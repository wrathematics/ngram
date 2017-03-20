/*  Copyright (c) 2014, 2017 Schmidt
    All rights reserved.
    
    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:
    
    1. Redistributions of source code must retain the above copyright notice,
    this list of conditions and the following disclaimer.
    
    2. Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
    
    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
    "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
    TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
    PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
    CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
    EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
    PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
    PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
    LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
    NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/


#ifndef __NGRAM_PLATFORM__
#define __NGRAM_PLATFORM__


// "portability"
#if (defined(__gnu_linux__) || defined(__linux__) || defined(__linux) || defined(linux))
#define OS_LINUX 1
#else
#define OS_LINUX 0
#endif

#if (defined(_WIN32) || defined(__WIN32__) || defined(_WIN64) || defined(__TOS_WIN__) || defined(__WINDOWS__))
#define OS_WINDOWS 1
#else
#define OS_WINDOWS 0
#endif

#if ((defined(__APPLE__) && defined(__MACH__)) || macintosh || Macintosh)
#define OS_MAC 1
#else
#define OS_MAC 0
#endif

#if defined(__FreeBSD__)
#define OS_FREEBSD 1
#else
#define OS_FREEBSD 0
#endif

#if (defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__bsdi__) || defined(__DragonFly__))
#define OS_BSD 1
#else
#define OS_BSD 0
#endif

#if (defined(__sun) || defined(sun))
#define OS_SOLARIS 1
#else
#define OS_SOLARIS 0
#endif

// why the hell not
#if (defined(__GNU__) || defined(__gnu_hurd__))
#define OS_HURD 1
#else
#define OS_HURD 0
#endif

#if (OS_BSD || OS_HURD || OS_LINUX || OS_MAC || OS_SOLARIS)
#define OS_NIX 1
#else
#define OS_NIX 0
#endif


#endif
