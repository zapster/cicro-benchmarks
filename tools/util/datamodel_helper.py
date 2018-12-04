import json

from dateutil.parser import parse as date_parse

import util.datamodel as dm
from util.color_logger import get_logger
from util.auto_extend_list import auto_extend_list

logger = get_logger('datamodel_helper')


def get_benchmark_name(benchmark):
    return "{}.{}".format(benchmark.get('fixture'), benchmark.get('name'))


def load_file_in_db(session, file):
    file_data = json.load(file)

    harness_data = {}
    if 'benchmark_data' in file_data:
        benchmark_data = file_data['benchmark_data']
        harness_data = file_data.get('harness_data', {})
    else:
        benchmark_data = file_data  # old file structure

    execution_cache = {}

    for runtime_data in benchmark_data.values():
        for runtime, data in runtime_data.items():
            if type(data) is not list:
                data = [data]  # old file structure

            run_id = 0
            for entry in data:
                entry_h_data = harness_data.get(entry['harness'], {}).get(runtime, []) if 'harness' in entry else []
                h_data = entry_h_data[run_id] if len(entry_h_data) > run_id else {}

                harness_name = entry['harness']
                harness = session.query(dm.Harness).filter_by(name=harness_name).one_or_none()
                if harness is None:
                    harness = dm.Harness(name=harness_name)
                    session.add(harness)

                benchmark = session.query(dm.Benchmark).filter_by(name=get_benchmark_name(entry)).one_or_none()
                if benchmark is None:
                    benchmark = dm.Benchmark(name=get_benchmark_name(entry), harness=harness)
                    session.add(benchmark)
                assert benchmark.harness == harness

                config = session.query(dm.Configuration).filter_by(name=runtime, harness=harness).one_or_none()
                if config is None:
                    config = dm.Configuration(name=runtime, harness=harness)
                    session.add(config)

                h_system = h_data.get('system', {})
                h_cpu = h_system.get('cpu', {})
                h_memory = h_system.get('memory', {})

                execution_cache_arr = execution_cache.get(harness_name, {}).get(runtime, [])
                if run_id < len(execution_cache_arr) and execution_cache_arr[run_id] is not None:
                    execution = execution_cache[harness_name][runtime][run_id]
                else:
                    execution = dm.Execution(configuration=config,
                                             datetime=date_parse(h_data['datetime']) if 'datetime' in h_data else None,
                                             stderr=h_data.get('stderr'),
                                             stdout=h_data.get('stdout'),
                                             exit_code=h_data.get('exit_code'),
                                             sys_platform=h_system.get('platform'),
                                             sys_mem_avail=h_memory.get('available'),
                                             sys_mem_free=h_memory.get('free'),
                                             sys_mem_total=h_memory.get('total'),
                                             sys_mem_used=h_memory.get('used'),
                                             sys_cpu_logical=h_cpu.get('cores_logical'),
                                             sys_cpu_physical=h_cpu.get('cores_physical'))
                    session.add(execution)

                    session.add_all([dm.ExecutionBuildSystem(execution=execution, key=key, value=value)
                                     for key, value in h_data.get('build_system', {}).items()])

                    session.add_all([dm.ExecutionMakeEnv(execution=execution, key=key, value=value)
                                     for key, value in h_data.get('make_env', {}).items()])

                    session.add_all([dm.ExecutionSystemCpu(execution=execution, idx=idx, percent=val[0],
                                                           cur_clock=val[1][0], min_clock=val[1][1],
                                                           max_clock=val[1][2])
                                     for idx, val in enumerate(zip(h_cpu.get('percent', []), h_cpu.get('freq', [])))])

                    # store in execution cache
                    if harness_name not in execution_cache:
                        execution_cache[harness_name] = {}
                    if runtime not in execution_cache[harness_name]:
                        execution_cache[harness_name][runtime] = auto_extend_list(None)
                    execution_cache[harness_name][runtime][run_id] = execution

                run = dm.Run(execution=execution,
                             benchmark=benchmark,
                             clock_resolution=entry.get('clock_resolution'),
                             clock_resolution_measured=entry.get('clock_resolution_measured'),
                             clock_type=entry.get('clock_type'),
                             disabled=entry.get('disabled'),
                             iterations_per_run=entry.get('iterations_per_run'))

                for idx, dp in enumerate(entry['runs']):
                    session.add_all([dm.Datapoint(idx=idx, run=run, key=key, value=value) for key, value in dp.items()])

                session.commit()

                run_id += 1
    return True
