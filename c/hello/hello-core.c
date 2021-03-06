/*
 * Copyright (C) 2015 by Yen-Chin, Lee <coldnew.tw at gmail.com>
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
#include <string.h>
#include <assert.h>
#include <emacs-module.h>

//`plugin_is_GPL_compatible' indicates that its code is released under the GPL
// or compatible license; Emacs will refuse to load modules that don't export
// such a symbol.
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

/* Module init function.  */
int
emacs_module_init(struct emacs_runtime *ert)
{
        emacs_env *env = ert->get_environment(ert);

        emacs_value hellofn = env->make_function(env, 0, 0, Fcall_hello, "return hello string", NULL);

        // Bind NAME to FUN.
        // (fset 'hello-c '(lambda () "Hello Emacs"))
        emacs_value Qfset = env->intern(env, "fset");
        emacs_value Qsym = env->intern(env, "hello-c");
        emacs_value fset_args[] = { Qsym, hellofn };

        env->funcall(env, Qfset, 2, fset_args);

        // Provide FEATURE to Emacs.
        // (provide 'hello-core)
        emacs_value Qfeat = env->intern(env, "hello-core");
        emacs_value Qprovide = env->intern(env, "provide");
        emacs_value provide_args[] = { Qfeat };

        env->funcall(env, Qprovide, 1, provide_args);

        return 0;
}
