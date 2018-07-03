from functools import partial


def sulong_graalvm_executor(filepath, workdir, warmup, **kwargs):
    kwargs['warmup_iterations'] = warmup
    return wllvm_executor(filepath, workdir, '$GRAALVM_DIR/lli', **kwargs)


def sulong_latest_executor(filepath, workdir, warmup, **kwargs):
    kwargs['warmup_iterations'] = warmup
    kwargs['timeout'] = 10000
    return wllvm_executor(filepath, workdir, '$SULONG_LATEST_CMD', **kwargs)


sulong_env = {
    "CC": "$(WLLVM_DIR)/wllvm",
    "AS": "$(WLLVM_DIR)/wllvm",
    "CFLAGS": "-Wno-everything -O1",
    "PAPI": 0
}

harness.add_runtime('sulong-graalvm', sulong_env, make_func=wllvm_make, exec_func=partial(sulong_graalvm_executor, warmup=100))

harness.add_runtime('sulong-warmup-0', sulong_env, make_func=wllvm_make, exec_func=partial(sulong_latest_executor, warmup=0))
harness.add_runtime('sulong-warmup-1', sulong_env, make_func=wllvm_make, exec_func=partial(sulong_latest_executor, warmup=1))
harness.add_runtime('sulong-warmup-2', sulong_env, make_func=wllvm_make, exec_func=partial(sulong_latest_executor, warmup=2))
harness.add_runtime('sulong-warmup-10', sulong_env, make_func=wllvm_make, exec_func=partial(sulong_latest_executor, warmup=10))
harness.add_runtime('sulong-warmup-100', sulong_env, make_func=wllvm_make, exec_func=partial(sulong_latest_executor, warmup=100))
harness.add_runtime('sulong-warmup-1000', sulong_env, make_func=wllvm_make, exec_func=partial(sulong_latest_executor, warmup=1000))
harness.add_runtime('sulong-warmup-10000', sulong_env, make_func=wllvm_make, exec_func=partial(sulong_latest_executor, warmup=10000))
