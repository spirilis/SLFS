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
/// @defgroup slfs_errnos SLFS Library-native Error Codes
/// @{

#define SLFS_LIB_ERR_FILE_NOT_OPEN         -10001  ///< File operation intended for an open file when SerFlash object has no file open
#define SLFS_LIB_ERR_FILE_OPEN_FOR_WRITE   -10002  ///< File operation requires read-mode but the SerFlash object has a file open for write
#define SLFS_LIB_ERR_FILE_OPEN_FOR_READ    -10003  ///< File operation requires write-mode but the SerFlash object has a file open for read
#define SLFS_LIB_ERR_FILE_ALREADY_OPEN     -10004  ///< File operation requiring an unreferenced or unopen file when SerFlash object has a file open */
#define SLFS_LIB_ERR_OFFSET_OUT_OF_BOUNDS  -10005  ///< File position seek attempted to out-of-bounds position

/// @}


class SLFS : public Stream {
    private:
        int32_t filehandle;
        int32_t filesize, offset;
        int32_t retval;
        boolean is_write;

        
    public:
        SLFS();  ///< Constructor
        /// @defgroup admin_funcs Administrative and whole-file operation functions
        /// @{

        ///
        /// @brief Initialize
        /// @details Ensure the SimpleLink API is initialized using WiFi.init()
        void begin(void);

        ///
        /// @brief Stop
        /// @details Does nothing, just included per Arduino API convention
        void end(void);

        ///
        /// @brief Open file
        /// @details Open a file for create, read or write as specified by @c mode
        /// @param filename String representing a file. @n
        ///        While the SimpleLink Filesystem has no intrinsic concept of directories,
        ///        you may use slashes in your filename to organize files in a conceptual
        ///        directory structure (and TI's system files utilize a UNIX-style forward-slash
        ///        convention for their own files likewise).
        /// @param mode SimpleLink API-native mode specifier.
        ///        @parblock
        ///        The following parameters are allowed for opening files:
        ///        @par SimpleLink Filesystem API modes
        ///        @c FS_MODE_OPEN_READ - Open file for reading  @n
        ///        @c FS_MODE_OPEN_WRITE - Open existing file for writing @n
        ///        @c FS_MODE_OPEN_CREATE(size,opts) - Create a new file, destroying the old one if an existing file with identical filename existed. @n
        ///        @par FS_MODE_OPEN_CREATE parameters
        ///        @c size - Maximum size of file, in bytes.  Note the SimpleLink Filesystem allocates using a minimal block size of 4KB. @n
        ///        @c opts - A bitwise OR of the following attributes: @n
        ///        @c _FS_FILE_OPEN_FLAG_COMMIT - File is mirrored within the Serial Flash; this causes the file to use 2 times the amount of space. @n
        ///        @c _FS_FILE_OPEN_FLAG_SECURE - File is stored securely.  No documentation on what this means. @n
        ///        @c _FS_FILE_OPEN_FLAG_NO_SIGNATURE_TEST - Something related to Secure storage.  No documentation on what this means. @n
        ///        @c _FS_FILE_OPEN_FLAG_STATIC - Something related to Secure storage.  No documentation on what this means. @n
        ///        @c _FS_FILE_OPEN_FLAG_VENDOR - Something related to Secure storage.  No documentation on what this means. @n
        ///        @c _FS_FILE_PUBLIC_WRITE - Something related to Secure storage.  No documentation on what this means. @n
        ///        @c _FS_FILE_PUBLIC_READ - Something related to Secure storage.  No documentation on what this means. @n
        ///        @endparblock
        /// @returns SL_FS_OK if successful, negative number if error
        int32_t open(const uint8_t *filename, int32_t mode);

        ///
        /// @brief Close file
        /// @details Close a previously-opened file
        /// @returns SL_FS_OK if successful, negative number if error
        int32_t close(void);

        ///
        /// @brief Delete file
        /// @details Delete a file by filename.
        /// @n
        /// While it is strictly possible per the SimpleLink Filesystem API to delete a file that is
        /// different from the one opened, this library has no way to determine whether the file
        /// specified for deletion is the same as the file presently open (we don't track the filename),
        /// so we default to disallowing any use of the del() function while a file is presently open.
        /// @n @n
        /// If it is necessary to work around this limitation, you may declare another instance of the
        /// SLFS class in your code and use that object to perform a del() against a different file.
        /// @returns SL_FS_OK if successful, negative number if error
        int32_t del(const uint8_t *filename);
        inline int32_t del(const char *filename);
        /// @}
        ///

        ///
        /// @defgroup errors Error reporting
        /// @{

        ///
        /// @brief Return errno code of last API call
        /// @details Returns current value of @c retval, a class-private variable representing the last
        ///          error code or return value of a SimpleLink API syscall or SLFS bounds-checking or
        ///          sanity-checking code.
        /// @returns Error code, typically <= 0 in value.
        int32_t lastError(void);
        ///
        /// @brief Error string description
        /// @details Get meaningful string description of the errno code supplied
        /// @param errno Error code, typically <= 0 in value.
        /// @returns const char string representing meaningful description of given errno code, or "ERR_UNKNOWN" if it's not a known error code.
        const char *getErrorString(int32_t errno);

        ///
        /// @brief Error string description of last API call
        /// @details Variant of getErrorString() which uses the class's private @c retval variable which represents the return code
        ///          for the last executed SimpleLink API call or last SLFS API call.
        /// @note The value of @c retval usually matches the last SimpleLink API call, but may be assigned instead to an SLFS-native
        ///       errno code if the last error was caused by the SLFS's own bounds-checking and sanity-checking code. @n
        ///       For example, if the SLFS object had no open file and the user performed an open() on a new file, the @c retval
        ///       variable would contain the return value of the sl_FsOpen() SimpleLink API syscall performed within the open()
        ///       function to open the file. @n
        ///       But if the user was running del() on a file when the SLFS object had a file already open, the @c retval parameter would
        ///       not contain any return code derived from a SimpleLink API syscall such as sl_FsDel(), instead it would contain the value
        ///       SLFS_LIB_ERR_FILE_ALREADY_OPEN which was produced by the sanity-checking code within SLFS's del() function.
        ///       Under this circumstance the last-known error code derived from a SimpleLink API syscall (as opposed to any SLFS-based
        ///       function) would no longer be known.
        /// @returns const char string representing meaningful description of last API return code, or "ERR_UNKNOWN" if it's not a known error code.
        const char *lastErrorString(void);
        /// @}
        ///

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
