/**
 * @file
 * @brief External sort algorithm.
 */

#ifndef SORT_INTERNAL_H
#define SORT_INTERNAL_H

/**
 * @brief Function to sort a temporary subfile and remove it.
 * @param[in] nb_split Index of the subfile in the array of files.
 * @param[in] filenames Array of file to sort names.
 * @param[in] filenames_sort Array of sorted file names.
 **/
void sort_sortFiles(unsigned long nb_split,
			 const char ** filenames,
			 const char ** filenames_sort);

/**
 * @brief Function to sort-merge a list of sorted subfiles.
 * @param[in] nb_split Index of the subfile in the array of files.
 * @param[in] filenames_sort Array of sorted file names.
 * @param[in] o_file Nome of the output file where sorted data are written.
 * @note It work in stream. Files are not fully loaded in memory.
 **/
void sort_combMerge(unsigned long nb_split,
			 const char ** filenames_sort,
			 const char * o_file);

#endif
