///
/// @file        SLFS.h
/// @brief        Header
/// @headerfile <>
/// @details    SimpleLink File System
/// @n
/// * Supports the CC3100/CC3200 SimpleLink Serial Flash API
/// @n
/// * Tested on TI CC3200 LaunchPad
///
/// @author        Eric Brundick for the Energia project
///
/// @date        2014
/// @version    101
///
/// @copyright    (C) 2014 Eric Brundick spirilis at linux dot com
/// @n
///  GNU Lesser General Public License
/// @n
///  This library is free software; you can redistribute it and/or
/// @n
///  modify it under the terms of the GNU Lesser General Public
/// @n
///  License as published by the Free Software Foundation; either
/// @n
///  version 2.1 of the License, or (at your option) any later version.
/// @n
/// @n
///  This library is distributed in the hope that it will be useful,
/// @n
///  but WITHOUT ANY WARRANTY; without even the implied warranty of
/// @n
///  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
/// @n
///  Lesser General Public License for more details.
/// @n
/// @n
///  You should have received a copy of the GNU Lesser General Public
/// @n
///  License along with this library; if not, write to the Free Software
/// @n
///  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
/// @note
/// * Rei Vilo 2015-12-29 Added self-documentation
/// @n Developed with [embedXcode+
/// @see http://embedXcode.weebly.com
///


#ifndef SLFS_H
#define SLFS_H

#include <Energia.h>
#include <WiFi.h>

// Errno values intrinsic to this library (not the SimpleLink API)
/** @defgroup slfs_errnos SLFS Library-native Error Codes
 * @{
 */
#define SLFS_LIB_ERR_FILE_NOT_OPEN         -10001  /**< File operation performed when SerFlash object has no file open */
#define SLFS_LIB_ERR_FILE_OPEN_FOR_WRITE   -10002  /**< File operation requires read-mode but the SerFlash object has a file open for write */
#define SLFS_LIB_ERR_FILE_OPEN_FOR_READ    -10003  /**< File operation requires write-mode but the SerFlash object has a file open for read */
#define SLFS_LIB_ERR_FILE_ALREADY_OPEN     -10004  /**< File operation performed when SerFlash object has a file open */
#define SLFS_LIB_ERR_OFFSET_OUT_OF_BOUNDS  -10005  /**< File position seek attempted to out-of-bounds position */
/** @} */


class SLFS : public Stream {
    private:
        int32_t filehandle;
        int32_t filesize, offset;
        int32_t retval;
        boolean is_write;

        
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
        const char *getErrorString(int32_t);
        const char *lastErrorString(void);

        virtual int32_t seek(int32_t);
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
