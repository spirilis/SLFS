///
/// @file        SLFS.h
/// @brief        Header
/// @details    SimpleLink File System
/// * Supports the CC3100/CC3200 SimpleLink Serial Flash API
/// * Tested on TI CC3200 LaunchPad
///
/// @author        Eric Brundick for the Energia project
///
/// @date        2014
/// @version    101
///
/// @copyright    (C) 2014 Eric Brundick spirilis at linux dot com
/// @n
/// @note
/// * Rei Vilo 2015-12-29 Added self-documentation
/// @n Developed with [embedXcode+
/// @see http://embedXcode.weebly.com
///

/* SimpleLink API - Filesystem
 * Supports the CC3100/CC3200 SimpleLink Serial Flash API
 * Tested on TI CC3200 LaunchPad
 *
 * Written by Eric Brundick for the Energia project
 * Copyright (C) 2014 Eric Brundick <spirilis at linux dot com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef SLFS_H
#define SLFS_H

#include <Energia.h>
#include <WiFi.h>

// Errno values intrinsic to this library (not the SimpleLink API)
#define SLFS_LIB_ERR_FILE_NOT_OPEN         -10001
#define SLFS_LIB_ERR_FILE_OPEN_FOR_WRITE   -10002
#define SLFS_LIB_ERR_FILE_OPEN_FOR_READ    -10003
#define SLFS_LIB_ERR_FILE_ALREADY_OPEN     -10004


class SLFS : public Stream {
    private:
        int32_t filehandle;
        int32_t filesize, offset;
        int32_t retval;
        boolean is_write;

        const char * getSlErrorCode(int32_t);
        
    public:
        SLFS();
        void begin(void);
        void end(void);
        int32_t open(const uint8_t *filename, int32_t mode);
        inline int32_t open(const char *filename, int32_t mode);
        int32_t close(void);
        int32_t del(const uint8_t *filename);
        inline int32_t del(const char *filename);

        int32_t lastError(void);
        const char *lastErrorString(void);

        virtual boolean seek(int32_t);
        virtual size_t size(void);
        virtual int available(void);
        virtual int peek(void);
        virtual int read(void);
        size_t readBytes(void *, size_t);
        virtual void flush(void);
        virtual size_t write(uint8_t c);
        virtual size_t write(const uint8_t *, size_t);
        virtual size_t write(const void *a, size_t b);
        operator bool();
        using Print::write;
};

extern SLFS SerFlash;

#endif /* SLFS_H */
