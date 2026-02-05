
#include <stdio.h>
#include <stdlib.h>

#include <system_utils/system_utils.h>

#include <sort/demo.h>
#include <sort/sort.h>
#include "sort_internal.h"

/**
 * @brief Type of the sort algorithm used in the demo.
 **/
//#define SORTALGO(nb_elem, values) SU_ISort(nb_elem, values)
//#define SORTALGO(nb_elem, values) SU_HSort(nb_elem, values)
#define SORTALGO(nb_elem, values) SU_QSort(nb_elem, values)


void demoSortSplit(const char* i_file, const char* o_file) {
  unsigned long nb_lines = SU_getFileNbLine(i_file);
  fprintf(stderr, "Demo version with 3 split of %lu lines\n", nb_lines / 3);

  SU_splitFile(i_file, nb_lines / 3, 3, "/tmp/test-split-a.txt",
               "/tmp/test-split-b.txt", "/tmp/test-split-c.txt");

  int* values1 = NULL;
  unsigned long nb_elem1 = SU_loadFile("/tmp/test-split-a.txt", &values1);
  SU_removeFile("/tmp/test-split-a.txt");
  fprintf(stderr, "F1: Array of %lu elem\n", nb_elem1);
  SORTALGO(nb_elem1, values1);
  SU_saveFile("/tmp/test-split-a-sort.txt", nb_elem1, values1);
  free(values1);

  int* values2 = NULL;
  unsigned long nb_elem2 = SU_loadFile("/tmp/test-split-b.txt", &values2);
  SU_removeFile("/tmp/test-split-b.txt");
  fprintf(stderr, "F2: Array of %lu elem\n", nb_elem2);
  SORTALGO(nb_elem2, values2);
  SU_saveFile("/tmp/test-split-b-sort.txt", nb_elem2, values2);
  free(values2);

  fprintf(stderr, "Start merge sort\n");
  SU_mergeSortedFiles("/tmp/test-split-a-sort.txt",
                      "/tmp/test-split-b-sort.txt", "/tmp/test-res-tmp.txt");

  SU_removeFile("/tmp/test-split-a-sort.txt");
  SU_removeFile("/tmp/test-split-b-sort.txt");

  int* values3 = NULL;
  unsigned long nb_elem3 = SU_loadFile("/tmp/test-split-c.txt", &values3);
  SU_removeFile("/tmp/test-split-c.txt");
  fprintf(stderr, "F3: Array of %lu elem\n", nb_elem3);
  SORTALGO(nb_elem3, values3);
  SU_saveFile("/tmp/test-split-c-sort.txt", nb_elem3, values3);
  free(values3);

  fprintf(stderr, "Start merge sort 2\n");
  SU_mergeSortedFiles("/tmp/test-res-tmp.txt", "/tmp/test-split-c-sort.txt",
                      o_file);

  SU_removeFile("/tmp/test-split-c-sort.txt");
  SU_removeFile("/tmp/test-res-tmp.txt");
}

void demoSort(const char* i_file, const char* o_file) {
  fprintf(stderr, "Demo version sort\n");

  int* values = NULL;
  unsigned long nb_elem = SU_loadFile(i_file, &values);

  SORTALGO(nb_elem, values);

  SU_saveFile(o_file, nb_elem, values);

  free(values);
  fprintf(stderr, "End\n");
}
