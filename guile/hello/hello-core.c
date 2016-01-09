/*
 * Copyright (C) 2016 by Yen-Chin, Lee <coldnew.tw at gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <emacs-module.h>
#include <libguile.h>

//`plugin_is_GPL_compatible' indicates that its code is released under the GPL
// or compatible license; Emacs will refuse to load modules that don't export
// such a symbol.
int plugin_is_GPL_compatible;

const char *
hello()
{
        scm_init_guile();

        scm_c_primitive_load("hello.scm");

        SCM func = scm_variable_ref(scm_c_lookup("hello"));
        SCM retval = scm_call_0(func);

        char *str = scm_to_locale_string(retval);

        return str;
}

static emacs_value
Fcall_hello(emacs_env *env, ptrdiff_t nargs, emacs_value args[], void *data)
{
        const char *str = hello();
        return env->make_string(env, str, strlen(str));
}

// Lisp utilities for easier readability (simple wrappers).

// Provide FEATURE to Emacs.
        static void
                provide (emacs_env *env, const char *feature)
        {
                emacs_value Qfeat = env->intern (env, feature);
                emacs_value Qprovide = env->intern (env, "provide");
                emacs_value args[] = { Qfeat };

                env->funcall (env, Qprovide, 1, args);
        }

// Bind NAME to FUN.
        static void
                bind_function (emacs_env *env, const char *name, emacs_value Sfun)
        {
                emacs_value Qfset = env->intern (env, "fset");
                emacs_value Qsym = env->intern (env, name);
                emacs_value args[] = { Qsym, Sfun };

                env->funcall (env, Qfset, 2, args);
        }

// Module init function.
        int
                emacs_module_init(struct emacs_runtime *ert)
        {
                emacs_env *env = ert->get_environment(ert);

#define DEFUN(lsym, csym, amin, amax, doc, data)                        \
                bind_function (env, lsym,                               \
                               env->make_function (env, amin, amax, csym, doc, data))

                        DEFUN ("hello-c", Fcall_hello, 0, 0, "Return \"Hello Emacs\".", NULL);

#undef DEFUN

                        provide(env, "hello-core");
                        return 0;
        }
