#ifdef __cplusplus
extern "C" {
#endif

#ifndef VW_PREDICT_MODEL_H_
#define VW_PREDICT_MODEL_H_

#include <stdio.h>
#include <time.h>
#include <string.h>
//#include <predict_model.h>
//#include <predict_variable_util.h>



int  load_vw_model_from_file(char *model_ver_name, const char* file_path);

//Exposing method for testing purpose

void vw_model_test(char *model_path,char *model_ver_name);

#endif /* VW_PREDICT_TEST_H_ */

#ifdef __cplusplus
}
#endif
