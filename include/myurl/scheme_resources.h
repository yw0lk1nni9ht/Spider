/*
 Copyright (C) 2016-2017 Alexander Borisov

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA

 Author: lex.borisov@gmail.com (Alexander Borisov)
*/

#ifndef MyURL_SCHEME_RESOURCES_H
#define MyURL_SCHEME_RESOURCES_H
#pragma once

#define MyURL_SCHEME_STATIC_INDEX_LENGTH 31

static const myurl_scheme_entry_t myurl_scheme_entry_static_index[] =
{
	{NULL, 0, MyURL_SCHEME_ID_UNDEF, 0, MyURL_SCHEME_TYPE_UNDEF, 0, 0},
	{NULL, 0, MyURL_SCHEME_ID_UNDEF, 0, MyURL_SCHEME_TYPE_UNDEF, 0, 0},
	{"https", 5, MyURL_SCHEME_ID_HTTPS, 443, MyURL_SCHEME_TYPE_SPECIAL|MyURL_SCHEME_TYPE_HTTP_S, 0, 2},
	{NULL, 0, MyURL_SCHEME_ID_UNDEF, 0, MyURL_SCHEME_TYPE_UNDEF, 0, 0},
	{NULL, 0, MyURL_SCHEME_ID_UNDEF, 0, MyURL_SCHEME_TYPE_UNDEF, 0, 0},
	{NULL, 0, MyURL_SCHEME_ID_UNDEF, 0, MyURL_SCHEME_TYPE_UNDEF, 0, 0},
	{NULL, 0, MyURL_SCHEME_ID_UNDEF, 0, MyURL_SCHEME_TYPE_UNDEF, 0, 0},
	{NULL, 0, MyURL_SCHEME_ID_UNDEF, 0, MyURL_SCHEME_TYPE_UNDEF, 0, 0},
	{"blob", 4, MyURL_SCHEME_ID_BLOB, 0, MyURL_SCHEME_TYPE_LOCAL|MyURL_SCHEME_TYPE_FETCH, 0, 8},
	{NULL, 0, MyURL_SCHEME_ID_UNDEF, 0, MyURL_SCHEME_TYPE_UNDEF, 0, 0},
	{"file", 4, MyURL_SCHEME_ID_FILE, 0, MyURL_SCHEME_TYPE_SPECIAL|MyURL_SCHEME_TYPE_FETCH, 0, 10},
	{NULL, 0, MyURL_SCHEME_ID_UNDEF, 0, MyURL_SCHEME_TYPE_UNDEF, 0, 0},
	{"wss", 3, MyURL_SCHEME_ID_WSS, 443, MyURL_SCHEME_TYPE_SPECIAL, 0, 12},
	{NULL, 0, MyURL_SCHEME_ID_UNDEF, 0, MyURL_SCHEME_TYPE_UNDEF, 0, 0},
	{NULL, 0, MyURL_SCHEME_ID_UNDEF, 0, MyURL_SCHEME_TYPE_UNDEF, 0, 0},
	{"filesystem", 10, MyURL_SCHEME_ID_FILESYSTEM, 0, MyURL_SCHEME_TYPE_LOCAL|MyURL_SCHEME_TYPE_FETCH, 0, 15},
	{NULL, 0, MyURL_SCHEME_ID_UNDEF, 0, MyURL_SCHEME_TYPE_UNDEF, 0, 0},
	{NULL, 0, MyURL_SCHEME_ID_UNDEF, 0, MyURL_SCHEME_TYPE_UNDEF, 0, 0},
	{"ftp", 3, MyURL_SCHEME_ID_FTP, 21, MyURL_SCHEME_TYPE_SPECIAL|MyURL_SCHEME_TYPE_NETWORK, 0, 18},
	{NULL, 0, MyURL_SCHEME_ID_UNDEF, 0, MyURL_SCHEME_TYPE_UNDEF, 0, 0},
	{"data", 4, MyURL_SCHEME_ID_DATA, 0, MyURL_SCHEME_TYPE_LOCAL|MyURL_SCHEME_TYPE_FETCH, 0, 20},
	{"gopher", 6, MyURL_SCHEME_ID_GOPHER, 70, MyURL_SCHEME_TYPE_SPECIAL, 0, 21},
	{NULL, 0, MyURL_SCHEME_ID_UNDEF, 0, MyURL_SCHEME_TYPE_UNDEF, 0, 0},
	{NULL, 0, MyURL_SCHEME_ID_UNDEF, 0, MyURL_SCHEME_TYPE_UNDEF, 0, 0},
	{NULL, 0, MyURL_SCHEME_ID_UNDEF, 0, MyURL_SCHEME_TYPE_UNDEF, 0, 0},
	{NULL, 0, MyURL_SCHEME_ID_UNDEF, 0, MyURL_SCHEME_TYPE_UNDEF, 0, 0},
	{NULL, 0, MyURL_SCHEME_ID_UNDEF, 0, MyURL_SCHEME_TYPE_UNDEF, 0, 0},
	{"about", 5, MyURL_SCHEME_ID_ABOUT, 0, MyURL_SCHEME_TYPE_LOCAL|MyURL_SCHEME_TYPE_FETCH, 0, 27},
	{NULL, 0, MyURL_SCHEME_ID_UNDEF, 0, MyURL_SCHEME_TYPE_UNDEF, 0, 0},
	{"ws", 2, MyURL_SCHEME_ID_WS, 80, MyURL_SCHEME_TYPE_SPECIAL, 0, 29},
	{NULL, 0, MyURL_SCHEME_ID_UNDEF, 0, MyURL_SCHEME_TYPE_UNDEF, 0, 0},
	{"http", 4, MyURL_SCHEME_ID_HTTP, 80, MyURL_SCHEME_TYPE_SPECIAL|MyURL_SCHEME_TYPE_HTTP_S, 0, 31},
};


#endif /* MyURL_SCHEME_RESOURCES_H */
