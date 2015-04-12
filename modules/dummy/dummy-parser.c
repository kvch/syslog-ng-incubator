/*
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published
 * by the Free Software Foundation, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * As an additional exemption you are allowed to compile & link against the
 * OpenSSL libraries as published by the OpenSSL project. See the file
 * COPYING for details.
 *
 */

#include "driver.h"
#include "cfg-parser.h"
#include "dummy-grammar.h"

extern int dummy_debug;

int dummy_parse(CfgLexer *lexer, LogDriver **instance, gpointer arg);

static CfgLexerKeyword dummy_keywords[] = {
  { "dummy_dest",   KW_DUMMY_DEST },
  { "root_path",    KW_PATH },
  { "yes_no",       KW_YESNO },
  { "maximum",      KW_MAX },

  { "dummy_src",    KW_DUMMY_SRC },
  { "name",         KW_NAME },
  { "minimum",      KW_MIN },

  { NULL }
};

CfgParser dummy_parser =
{
#if ENABLE_DEBUG
  .debug_flag = &dummy_debug,
#endif
  .name = "dummy",
  .keywords = dummy_keywords,
  .parse = (gint (*)(CfgLexer *, gpointer *, gpointer)) dummy_parse,
  .cleanup = (void (*)(gpointer)) log_pipe_unref,
};

CFG_PARSER_IMPLEMENT_LEXER_BINDING(dummy_, LogDriver **)
