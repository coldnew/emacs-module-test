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
#include <assert.h>
#include <string>
#include <iostream>
#include <regex>
#include <emacs-module.h>

//`plugin_is_GPL_compatible' indicates that its code is released under the GPL
// or compatible license; Emacs will refuse to load modules that don't export
// such a symbol.
int plugin_is_GPL_compatible;


static inline
std::string ltrim(const std::string &s)
{
    static const std::regex lws{"^[ \t\n\r]+", std::regex_constants::extended};
    return std::regex_replace(s, lws, "");
}

static inline
std::string rtrim(const std::string &s)
{
    static const std::regex rws{"[ \t\n\r]+$", std::regex_constants::extended};
    return std::regex_replace(s, rws, "");
}

static inline
std::string trim(const std::string& s)
{
    return ltrim(rtrim(s));
}

static emacs_value
Fcall_ltrim(emacs_env *env, ptrdiff_t nargs, emacs_value args[], void *data) EMACS_NOEXCEPT
{
    emacs_value str = args[0];
    ptrdiff_t size = 0;
    char *buf = NULL;

    env->copy_string_contents(env, str, buf, &size);
    buf = (char *) malloc(size);
    env->copy_string_contents(env, str, buf, &size);

    std::string s2(buf);
    free(buf);

    std::string s = ltrim(s2);
    return env->make_string(env, s.c_str(), s.length());
}

static emacs_value
Fcall_rtrim(emacs_env *env, ptrdiff_t nargs, emacs_value args[], void *data) EMACS_NOEXCEPT
{
    emacs_value str = args[0];
    ptrdiff_t size = 0;
    char *buf = NULL;

    env->copy_string_contents(env, str, buf, &size);
    buf = (char *) malloc(size);
    env->copy_string_contents(env, str, buf, &size);

    std::string s2(buf);
    free(buf);

    std::string s = rtrim(s2);
    return env->make_string(env, s.c_str(), s.length());
}

static emacs_value
Fcall_trim(emacs_env *env, ptrdiff_t nargs, emacs_value args[], void *data) EMACS_NOEXCEPT
{
    emacs_value str = args[0];
    ptrdiff_t size = 0;
    char *buf = NULL;

    env->copy_string_contents(env, str, buf, &size);
    buf = (char *) malloc(size);
    env->copy_string_contents(env, str, buf, &size);

    std::string s2(buf);
    free(buf);

    std::string s = trim(s2);
    return env->make_string(env, s.c_str(), s.length());
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
    bind_function (env, lsym,                                           \
                   env->make_function (env, amin, amax, csym, doc, data))

    DEFUN ("sc-trim-left", Fcall_ltrim, 1, 1, "Remove whitespace at the beginning of S.", NULL);
    DEFUN ("sc-trim-right", Fcall_rtrim, 1, 1, "Remove whitespace at the end of S.", NULL);
    DEFUN ("sc-trim", Fcall_trim, 1, 1, "Remove whitespace at the beginning and end of S.", NULL);

#undef DEFUN

    provide(env, "sc-core");
    return 0;
}
