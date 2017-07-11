/*
 Copyright © Microsoft Corp 2012-2014, Yahoo! Inc. 2007-2012, and many
 individual contributors.

 All rights reserved.

 Redistribution and use in source and binary forms, with or without

 modification, are permitted provided that the following conditions are met:

 * Redistributions of source code must retain the above copyright

 notice, this list of conditions and the following disclaimer.

 * Redistributions in binary form must reproduce the above copyright

 notice, this list of conditions and the following disclaimer in the

 documentation and/or other materials provided with the distribution.

 * Neither the name of the Microsoft Corp nor the

 names of its contributors may be used to endorse or promote products

 derived from this software without specific prior written permission.



 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND

 ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED

 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE

 DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY

 DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES

 (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;

 LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND

 ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT

 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS

 SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include "vw_predict_model.h"

#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include "vowpalwabbit/parser.h"
#include "vowpalwabbit/vw.h"
#include "vowpalwabbit/ezexample.h"
#include <fstream>
#include <string>
#include <iostream>
#include <map>

#define CUSTOM_FORMAT(strp, format, ...) asprintf((strp), (format), ## __VA_ARGS__)
#define PTR_FREE(ptr) {free(ptr); ptr = NULL;}

#define vw_load_model_template "--link logistic --loss_function logistic -t  -i %s"

pthread_rwlock_t vw_pmodel_rwlock = PTHREAD_RWLOCK_INITIALIZER;

std::map<char*, vw*> vw_prediction_model;

using namespace std;

double predict_vw_probability(string  vw_string, char *model_ver_name) {
	printf("1: predict_vw_probability \n");
	double prob=-1.0;
	if (model_ver_name != NULL && strlen(model_ver_name) > 0
			&& vw_string.length() > 0) {
		//Read lock for getting Probability
		pthread_rwlock_rdlock(&vw_pmodel_rwlock);

		example *vec2 = VW::read_example(*vw_prediction_model[model_ver_name],
				vw_string);
		vw_prediction_model[model_ver_name]->learn(vec2);
		prob = vec2->pred.prob;
		VW::finish_example(*vw_prediction_model[model_ver_name], vec2);

		//Releasing Read lock
		pthread_rwlock_unlock(&vw_pmodel_rwlock);
	}
	//Safe case if model or vw string is empty;
	cout << "In predict_vw_probability Prob of : " << " : " << prob << endl;
	return prob;
}


int load_vw_model_from_file(char *model_ver_name, const char* file_path) {
	printf("loading model %s \n", file_path);
	int st=1;
	char commandBuf[512];
	int existsAndRead;
	sprintf(commandBuf, "test -f %s && test -r %s", file_path, file_path);
	existsAndRead = system(commandBuf);
	if (0 != existsAndRead) {
		 printf("existsAndRead error  \n");
		return 0;
	}
	//removing old model from
	printf("Removing old model \n");
	pthread_rwlock_wrlock(&vw_pmodel_rwlock);
	printf("printing old map ");
	 // show content
	  for (map<char*, vw*>::iterator it=vw_prediction_model.begin(); it!=vw_prediction_model.end(); ++it)
		  cout << it->first << " => " << it->second << '\n';
	if (vw_prediction_model[model_ver_name] != NULL) {
		printf("Found Older model in Map so removing \n");
		VW::finish(*vw_prediction_model[model_ver_name],true);
		vw_prediction_model[model_ver_name] = NULL;
	}
	printf("Removing old model Done\n");
	char *vw_model_tem;
	CUSTOM_FORMAT(&vw_model_tem, vw_load_model_template, file_path);
	std::string m_path(vw_model_tem);
	printf("Loading New Inhouse Model model =%s \n",vw_model_tem);
	vw_prediction_model[model_ver_name] = VW::initialize(m_path);
	if (NULL == vw_prediction_model[model_ver_name]) {
		st = 0;
	}
	pthread_rwlock_unlock(&vw_pmodel_rwlock);
	PTR_FREE(vw_model_tem);
	printf("load_vw_model_from_file status =%d \n",st);
	return st ;
}

//SOME functions for standalone testing purpose

//****************************************************  TESTING *************************************


void vw_model_test(char* model_path,char* model_ver_name) {
	//char model_ver_name[32] = "VW_INHOUSE_CLICK_10_1";
	clock_t start, finish;
	start = clock();
	int st = load_vw_model_from_file(model_ver_name, model_path);
	finish = clock();
	double total = ((double) (finish - start) / CLOCKS_PER_SEC) * 1000000000;
	printf("model loaded successfully status = %d time taken =%lf ns \n",
			(int) st, total);
	ifstream file("vw_test_new.txt");
	string str, token;
	int index = 0;
	clock_t mainstart = clock();
	while (std::getline(file, str)) {
		index++;
		if (index == 1)
			continue;
	 string vw_pred_string("|i feature1:9 feature2:7 feature3:5 feature4:10 feature:0|c adv_id_6957 creative_id_78285 interactive_feature_2_300X250 site_id_554766299 aggregator_id_7 connectionType_3 feature5_2 feature6_0 country_id_101 feature7_c region_id_101X0") ;	
	//string vw_pred_string =	make_dummy_pred_attributes_from_comma_string(str);
		printf("vw_pred_string st = %s \n", vw_pred_string.c_str());
		start = clock();
		double prob=0.0;
		prob = predict_vw_probability(vw_pred_string, model_ver_name);
		finish = clock();
		total = ((double) (finish - start) / CLOCKS_PER_SEC) * 1000000000;
		cout << "Prob of : " << index << " : " << prob << " :: time taken "
				<< total << " ns.\n";
	}
}
