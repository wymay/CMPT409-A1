// ErdosNumber

#include <cstdio>
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <sstream>
#include <algorithm>

using namespace std;

// a function to split a string based on a delimiter and return a vector of substrings
vector<string> split(string str,char delimiter){
	stringstream ss(str);
    vector<string> output;

    while( ss.good() )
    {
        string substr;
        getline( ss, substr, delimiter);
        output.push_back( substr );
    }

    return output;
}

int main(){

    // maintain the number of scenario
    int n;
    cin >> n;
    int scenarioNum = 1;
    // iterate over the scenarios
    while(n--)
    {
        // read the number of papers and authors
        int P, N;
        cin >> P >> N;

        // iterate over papers and extract authors of each paper
        vector<string> authors[P];
        for(int i = 0; i < P; i++)
        {
            vector<string> temp_list;
			string line_part_1, line_part_2;
			getline(cin, line_part_1, ':');
			getline(cin, line_part_2);
			temp_list = split(line_part_1, ',');
			for(int j = 0; j < temp_list.size(); j=j+2)
			{

				string full_name = (temp_list[j] + ',' + temp_list[j+1]);

                // "erase–remove idiom" see wikipedia to learn about
				if(j == 0)
				    full_name.erase(remove(full_name.begin(), full_name.end(), '\n'), full_name.end());

                // remove space from the beginning if exist
				if(full_name[0] == ' ')
		    		full_name.erase(full_name.begin());

                // a new author for the i'th paper
                full_name.erase( 0, full_name.find_first_not_of(" ") );  
                full_name.erase( full_name.find_last_not_of(" ") + 1 );
                authors[i].push_back(full_name);
			}
        }

        // make an array of authors to report their "Erdos Number"
        string name_list[N];
		for(int i = 0; i < N; i++){
			getline(cin, name_list[i]);
		}
        
        map< string, set< string > > relations;
        // for every paper
        for( int i = 0; i < P; i++ ){
            vector< string > paper = authors[i];
            // paperData is every paper authers names pointer
            string* paperData = paper.data();
            // for every auther in paper
            for( int j = 0; j < paper.size(); j++ ){
                auto temp = relations.find( paperData[j] );
                if( temp == relations.end() ){
                    set< string > names;
                    for ( int k = 0; k < paper.size(); k++ ){
                        if( k != j ) names.insert( paperData[k] );
                    }
                    relations.insert( pair< string, set<string > >( paperData[j], names ) );
                } else {
                    set< string > names = temp->second;
                    for ( int k = 0; k < paper.size(); k++ ){
                        if( k != j ) names.insert( paperData[k] );
                    }
                    temp->second = names;
                }
            }
        }
        map< string, int > orderNum;
        queue< string > levelName;
        orderNum.insert( pair< string, int >( "Erdos, P.", 0 ) );
        string tempName = "Erdos, P.";
        levelName.push( tempName );
        while( !levelName.empty() ){
            tempName = levelName.front();
            levelName.pop();
            auto tempOrderName = relations.find( tempName );
            set< string > names = tempOrderName->second;
            for( auto it=names.begin(); it!=names.end(); ++it){
                auto tempOrder = orderNum.find( *it );
                if( tempOrder == orderNum.end() ){
                    int order = (orderNum.find( tempName ))->second + 1;
                    orderNum.insert( pair< string, int >(*it, order) );
                    levelName.push( *it );
                }
            }
            relations.erase( tempOrderName );
        }
        cout << "Scenario " << scenarioNum << "\n";
        for(int i = 0; i < N; i++){
            auto answerNum = orderNum.find( name_list[i] );
            if ( answerNum != orderNum.end() ){
                cout << name_list[i] << " " << answerNum->second << "\n";
            } else{
                cout << name_list[i] << " infinity\n";
            }
        }
        scenarioNum ++;
    }

	return 0;



}
