//
//  RunLength.cpp
//  
//
//  Created by Kim Ngo June 24, 2014.

//	Counts number of min runs
//  Compares min runs from significant sequences with non-sig seqs
//	SigOrf files are from Aaron's pruning results
//	mm_orfeome files are from minmax results

#include "RunLength.h"

#include <string>
#include <vector>
#include <utility>	// pair
#include <iostream>	// cout
#include <sstream> //stringstream peak, ignore

using namespace std;

RunLength :: RunLength (vector<string>::iterator sigOrf_it, const vector<string>& sigOrf_v, const vector<pair<string, string> >& id_seq) {

	set_sig_runs(100);
	set_non_sig_runs(100);
	count_runs(sigOrf_it, sigOrf_v, id_seq);
//	cout << endl << endl << "The next organism is " << *sigOrf << endl;
}


// Instantiates sig_run vector n 0's
void RunLength :: set_sig_runs(int n) {
	vector<int> temp(n, 0);
	sig_runs = temp;
}
void RunLength :: set_non_sig_runs(int n) {
	vector<int> temp(n, 0);
	non_sig_runs = temp;
}

// Returns # of runs for sig seqs
vector<int> RunLength :: get_sig_runs() {
	return sig_runs;
}


// Returns # of runs for non-sig seqs
vector<int> RunLength :: get_non_sig_runs() {
	return non_sig_runs;
}


// SEGFAULTS FOR SOME REASON :(
// Parses minmax sequence string into vector of floats
vector<float> RunLength :: parse_mm_seq(string &mm_seq) {

	float i;
	vector<float> mm_number_v;	// str parsed into a vector of floats
	stringstream ss(mm_seq);
	
	while (ss >> i) {
		mm_number_v.push_back(i);
		if (ss.peek() == ',')
			ss.ignore();
	}
	return mm_number_v;
}


// Returns the position the significant organism iterator was last at
vector<string>::iterator RunLength :: get_it_pos() {
	return sigOrf_it;
}


// Sets where the last position the iterator pointed to
void RunLength :: set_sigOrf_it_pos(vector<string>::iterator it) {
	sigOrf_it = it;
}


// Adds the count of each run length to the total sum
void RunLength :: add_runs (vector<int>& sum, const vector<int>& runs) {

	vector<int>::iterator sum_it = sum.begin();
	vector<int>::const_iterator runs_it = runs.begin();
	for (sum_it; sum_it != sum.end(); ++sum_it, ++runs_it) {
		*sum_it += *runs_it;
	}
}


// Prints vector of sig & non-sig runs
void RunLength :: print_runs (const vector<int>& sr, const vector<int>& nsr) {

	vector<int>::const_iterator sr_it = sr.begin();
	vector<int>::const_iterator nsr_it = nsr.begin();
	for (int i = 0; sr_it != sr.end(); i++, ++sr_it, ++nsr_it) {
		cout << i << " sig: " << *sr_it << " ";
		cout << "non-sig: " << *nsr_it << endl;
	}
/*	for (int i = 0; i < 25; i++) {
		cout << i << "\t" << "sig: " << sr[i] << "\t";
		cout << "non-sig: " << nsr[i] << endl;
	}
*/}


// Increments (non)sig_runs if vec of sig seqs has consecutive mins
// The address of the bin is the length of the run
// Value in the addr is the number of runs of that length
void RunLength :: count_runs(vector<string>::iterator sigOrf, const vector<string>& sigOrf_v, const vector< pair< string, string> >& id_seq) {

	int min_run_count = 0;

	// Iterates through pairs in the vector id_seq
	vector< pair< string, string> >::const_iterator id_seq_it = id_seq.begin();	
	for (id_seq_it; id_seq_it != id_seq.end(); ++id_seq_it) {
//		cout << id_seq_it->first << endl;


		// Parse the minmax values string by ','
		vector<float> mm_number_v;
		float i;
		stringstream ss(id_seq_it->second);
	
		while (ss >> i) {
//			cout << i << " ";
			mm_number_v.push_back(i);
			if (ss.peek() == ',')
				ss.ignore();
		}
//		cout << endl;
		
		// Iterates through min max values and counts for min runs
		vector<float>::iterator it = mm_number_v.begin();
		for (it; it != mm_number_v.end(); ++it) {

			min_run_count = 0;						// Reset count every max value break
			while (*it < 0) {							// Continuous min values
//				cout << *it << " ";
				min_run_count++;
				if (it+1 != mm_number_v.end())	// Prevents from running off vec
					++it;
				else break;
			}
//			if (min_run_count > 0)
//				cout << endl << min_run_count << endl;
			
			// If id matches significant orfeome, increment accordingly
			if (*sigOrf == id_seq_it->first && sigOrf+1 != sigOrf_v.end()) {
				sig_runs[min_run_count]++;
				++sigOrf;
//				cout << "Significant: " << sig_runs[min_run_count] << endl;
//				cout << "next significant seq: " << *sigOrf << endl << endl;

			} else {
				non_sig_runs[min_run_count]++;
//cout << "Not significant: " << non_sig_runs[min_run_count] << endl;
			}
		}
	}
	set_sigOrf_it_pos(sigOrf);
}