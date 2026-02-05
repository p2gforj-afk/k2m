/**
 * @file
 * @brief External sort algorithm.
 */

#ifndef SORT_SORT_H
#define SORT_SORT_H


/**
 * @brief Function to sort a file using an external sort and nb_split subfiles.
 * @param[in] i_file Name of the file to process.
 * @param[in] o_file Name of the output sorted file.
 * @param[in] nb_split Number of subfiles to use for the external sort.
 * @note No parallelisms.
 **/
void sort(const char * i_file, const char * o_file, unsigned long nb_split);

#endif // SORT_SORT_H
