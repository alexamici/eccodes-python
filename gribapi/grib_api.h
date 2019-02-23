/*
 * Copyright 2005-2018 ECMWF.
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 *
 * In applying this licence, ECMWF does not waive the privileges and immunities granted to it by
 * virtue of its status as an intergovernmental organisation nor does it submit to any jurisdiction.
 */

/*! \file grib_api.h
  \brief grib_api C header file

*/

/*! Grib handle,   structure giving access to parsed message values by keys
    \ingroup grib_handle
*/
typedef struct grib_handle    grib_handle;

/*! Grib context,  structure containing the memory methods, the parsers and the formats.
    \ingroup grib_context
*/
typedef struct grib_context   grib_context;

/*! @} */

/*! \defgroup grib_handle The grib_handle
The grib_handle is the structure giving access to parsed grib values by keys.
*/
/*! @{*/
/**
*  Counts the messages contained in a file resource.
*
* @param c           : the context from which the handle will be created (NULL for default context)
* @param f           : the file resource
* @param n           : the number of messages in the file
* @return            0 if OK, integer value on error
*/
int grib_count_in_file(grib_context* c, FILE* f,int* n);

/**
*  Create a handle from a file resource.
*  The file is read until a message is found. The message is then copied.
*  Remember always to delete the handle when it is not needed anymore to avoid
*  memory leaks.
*
* @param c           : the context from which the handle will be created (NULL for default context)
* @param f           : the file resource
* @param error       : error code set if the returned handle is NULL and the end of file is not reached
* @return            the new handle, NULL if the resource is invalid or a problem is encountered
*/
grib_handle* grib_handle_new_from_file(grib_context* c, FILE* f, int* error);

/**
 *  Create a handle from a GRIB message contained in the samples directory.
 *  The message is copied at the creation of the handle
 *
 * @param c           : the context from which the handle will be created (NULL for default context)
 * @param sample_name : the name of the sample file (without the .tmpl extension)
 * @return            the new handle, NULL if the resource is invalid or a problem is encountered
 */
grib_handle* grib_handle_new_from_samples (grib_context* c, const char* sample_name);

/**
*  Frees a handle, also frees the message if it is not a user message
*  @see  grib_handle_new_from_message
* @param h           : The handle to be deleted
* @return            0 if OK, integer value on error
*/
int   grib_handle_delete   (grib_handle* h);

/*! @} */

/*! \defgroup handling_coded_messages Handling coded messages */
/*! @{ */
/**
* getting the message attached to a handle
*
* @param h              : the handle to which the buffer should be gathered
* @param message        : the pointer to be set to the handle's data
* @param message_length : On exit, the message size in number of bytes
* @return            0 if OK, integer value on error
*/
int grib_get_message(grib_handle* h ,const void** message, size_t *message_length);

/**
*  Get the number of coded value from a key, if several keys of the same name are present, the total sum is returned
*
* @param h           : the handle to get the offset from
* @param key         : the key to be searched
* @param size        : the address of a size_t where the size will be set
* @return            0 if OK, integer value on error
*/
int         grib_get_size(grib_handle* h, const char* key,size_t *size);

/**
*  Get the length of the string representation of the key, if several keys of the same name are present, the maximum length is returned
*
* @param h           : the handle to get the offset from
* @param key         : the key to be searched
* @param length        : the address of a size_t where the length will be set
* @return            0 if OK, integer value on error
*/
int         grib_get_length(grib_handle* h, const char* key,size_t *length);

/**
*  Get a long value from a key, if several keys of the same name are present, the last one is returned
*  @see  grib_set_long
*
* @param h           : the handle to get the data from
* @param key         : the key to be searched
* @param value       : the address of a long where the data will be retrieved
* @return            0 if OK, integer value on error
*/
int          grib_get_long         (grib_handle* h, const char* key, long*   value);

/**
*  Get a double value from a key, if several keys of the same name are present, the last one is returned
*  @see  grib_set_double
*
* @param h           : the handle to get the data from
* @param key         : the key to be searched
* @param value       : the address of a double where the data will be retrieved
* @return            0 if OK, integer value on error
*/
int grib_get_double       (grib_handle* h, const char* key, double* value);

/**
*  Get a string value from a key, if several keys of the same name are present, the last one is returned
* @see  grib_set_string
*
* @param h           : the handle to get the data from
* @param key         : the key to be searched
* @param mesg       : the address of a string where the data will be retrieved
* @param length      : the address of a size_t that contains allocated length of the string on input, and that contains the actual length of the string on output
* @return            0 if OK, integer value on error
*/
int grib_get_string(grib_handle* h, const char* key, char* mesg, size_t *length);

/**
*  Set a long value from a key. If several keys of the same name are present, the last one is set
*  @see  grib_get_long
*
* @param h           : the handle to set the data to
* @param key         : the key to be searched
* @param val         : a long where the data will be read
* @return            0 if OK, integer value on error
*/
int grib_set_long         (grib_handle* h, const char*  key , long val);

/**
*  Set a string value from a key. If several keys of the same name are present, the last one is set
*  @see  grib_get_string
*
* @param h           : the handle to set the data to
* @param key         : the key to be searched
* @param mesg       : the address of a string where the data will be read
* @param length      : the address of a size_t that contains the length of the string on input, and that contains the actual packed length of the string on output
* @return            0 if OK, integer value on error
*/
int grib_set_string       (grib_handle* h, const char*  key , const char* mesg, size_t *length);

/**
*  Set a double array from a key. If several keys of the same name are present, the last one is set
*   @see  grib_get_double_array
*
* @param h           : the handle to set the data to
* @param key         : the key to be searched
* @param vals        : the address of a double array where the data will be read
* @param length      : a size_t that contains the length of the byte array on input
* @return            0 if OK, integer value on error
*/
int grib_set_double_array (grib_handle* h, const char*  key , const double*        vals   , size_t length);

/**
*  Get the API version
*
*  @return        API version
*/
long grib_get_api_version(void);

int grib_get_native_type(grib_handle* h, const char* name,int* type);

/*! \defgroup errors Error codes
Error codes returned by the grib_api functions.
*/
/*! @{*/
/** No error */
#define GRIB_SUCCESS		0
/** End of resource reached */
#define GRIB_END_OF_FILE		-1
/** Internal error */
#define GRIB_INTERNAL_ERROR		-2
/** Passed buffer is too small */
#define GRIB_BUFFER_TOO_SMALL		-3
/** Function not yet implemented */
#define GRIB_NOT_IMPLEMENTED		-4
/** Missing 7777 at end of message */
#define GRIB_7777_NOT_FOUND		-5
/** Passed array is too small */
#define GRIB_ARRAY_TOO_SMALL		-6
/** File not found */
#define GRIB_FILE_NOT_FOUND		-7
/** Code not found in code table */
#define GRIB_CODE_NOT_FOUND_IN_TABLE		-8
/** Array size mismatch */
#define GRIB_WRONG_ARRAY_SIZE		-9
/** Key/value not found */
#define GRIB_NOT_FOUND		-10
/** Input output problem */
#define GRIB_IO_PROBLEM		-11
/** Message invalid */
#define GRIB_INVALID_MESSAGE		-12
/** Decoding invalid */
#define GRIB_DECODING_ERROR		-13
/** Encoding invalid */
#define GRIB_ENCODING_ERROR		-14
/** Code cannot unpack because of string too small */
#define GRIB_NO_MORE_IN_SET		-15
/** Problem with calculation of geographic attributes */
#define GRIB_GEOCALCULUS_PROBLEM		-16
/** Memory allocation error */
#define GRIB_OUT_OF_MEMORY		-17
/** Value is read only */
#define GRIB_READ_ONLY		-18
/** Invalid argument */
#define GRIB_INVALID_ARGUMENT		-19
/** Null handle */
#define GRIB_NULL_HANDLE		-20
/** Invalid section number */
#define GRIB_INVALID_SECTION_NUMBER		-21
/** Value cannot be missing */
#define GRIB_VALUE_CANNOT_BE_MISSING		-22
/** Wrong message length */
#define GRIB_WRONG_LENGTH		-23
/** Invalid key type */
#define GRIB_INVALID_TYPE		-24
/** Unable to set step */
#define GRIB_WRONG_STEP		-25
/** Wrong units for step (step must be integer) */
#define GRIB_WRONG_STEP_UNIT		-26
/** Invalid file id */
#define GRIB_INVALID_FILE		-27
/** Invalid grib id */
#define GRIB_INVALID_GRIB		-28
/** Invalid index id */
#define GRIB_INVALID_INDEX		-29
/** Invalid iterator id */
#define GRIB_INVALID_ITERATOR		-30
/** Invalid keys iterator id */
#define GRIB_INVALID_KEYS_ITERATOR		-31
/** Invalid nearest id */
#define GRIB_INVALID_NEAREST		-32
/** Invalid order by */
#define GRIB_INVALID_ORDERBY		-33
/** Missing a key from the fieldset */
#define GRIB_MISSING_KEY		-34
/** The point is out of the grid area */
#define GRIB_OUT_OF_AREA		-35
/** Concept no match */
#define GRIB_CONCEPT_NO_MATCH		-36
/** Hash array no match */
#define GRIB_HASH_ARRAY_NO_MATCH		-37
/** Definitions files not found */
#define GRIB_NO_DEFINITIONS		-38
/** Wrong type while packing */
#define GRIB_WRONG_TYPE		-39
/** End of resource */
#define GRIB_END		-40
/** Unable to code a field without values */
#define GRIB_NO_VALUES		-41
/** Grid description is wrong or inconsistent */
#define GRIB_WRONG_GRID		-42
/** End of index reached */
#define GRIB_END_OF_INDEX		-43
/** Null index */
#define GRIB_NULL_INDEX		-44
/** End of resource reached when reading message */
#define GRIB_PREMATURE_END_OF_FILE		-45
/** An internal array is too small */
#define GRIB_INTERNAL_ARRAY_TOO_SMALL		-46
/** Message is too large for the current architecture */
#define GRIB_MESSAGE_TOO_LARGE		-47
/** Constant field */
#define GRIB_CONSTANT_FIELD		-48
/** Switch unable to find a matching case */
#define GRIB_SWITCH_NO_MATCH		-49
/** Underflow */
#define GRIB_UNDERFLOW		-50
/** Message malformed */
#define GRIB_MESSAGE_MALFORMED		-51
/** Index is corrupted */
#define GRIB_CORRUPTED_INDEX		-52
/** Invalid number of bits per value */
#define GRIB_INVALID_BPV		-53
/** Edition of two messages is different */
#define GRIB_DIFFERENT_EDITION		-54
/** Value is different */
#define GRIB_VALUE_DIFFERENT		-55
/** Invalid key value */
#define GRIB_INVALID_KEY_VALUE		-56
/** String is smaller than requested */
#define GRIB_STRING_TOO_SMALL		-57
/** Wrong type conversion */
#define GRIB_WRONG_CONVERSION		-58
/** Missing BUFR table entry for descriptor */
#define GRIB_MISSING_BUFR_ENTRY		-59
/** Null pointer */
#define GRIB_NULL_POINTER		-60
/** Attribute is already present, cannot add */
#define GRIB_ATTRIBUTE_CLASH		-61
/** Too many attributes. Increase MAX_ACCESSOR_ATTRIBUTES */
#define GRIB_TOO_MANY_ATTRIBUTES		-62
/** Attribute not found. */
#define GRIB_ATTRIBUTE_NOT_FOUND		-63
/** Edition not supported. */
#define GRIB_UNSUPPORTED_EDITION		-64
/** Value out of coding range */
#define GRIB_OUT_OF_RANGE		-65
/** Size of bitmap is incorrect */
#define GRIB_WRONG_BITMAP_SIZE		-66
/*! @}*/