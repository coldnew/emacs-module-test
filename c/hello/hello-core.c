#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <emacs-module.h>

int plugin_is_GPL_compatible;

const char *
hello()
{
        return "Hello Emacs";
}

static emacs_value
Fcall_hello(emacs_env *env, ptrdiff_t nargs, emacs_value args[], void *data)
{
        const char *str = hello();
        return env->make_string(env, str, strlen(str));
}

int
emacs_module_init(struct emacs_runtime *ert)
{
        emacs_env *env = ert->get_environment(ert);

        emacs_value hellofn = env->make_function(env, 0, 0, Fcall_hello, "return hello string", NULL);

        // Add emacs-lisp function `hello-c',
        // eq: (fset 'hello-c '(lambda () "Hello Emacs"))
        emacs_value Qfset = env->intern(env, "fset");
        emacs_value Qsym = env->intern(env, "hello-c");
        emacs_value fset_args[] = { Qsym, hellofn };

        env->funcall(env, Qfset, 2, fset_args);

        // provide this lib
        // eq: (provide 'hello-core)
        emacs_value Qfeat = env->intern(env, "hello-core");
        emacs_value Qprovide = env->intern(env, "provide");
        emacs_value provide_args[] = { Qfeat };

        env->funcall(env, Qprovide, 1, provide_args);

        return 0;
}
