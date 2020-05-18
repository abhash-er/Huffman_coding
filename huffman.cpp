#include <bits/stdc++.h>
using namespace std;

//building a binary Huffman-Node

class MinHeapNode{
public:	
	char source;
	double prob;
	
	MinHeapNode *left,*right;

	MinHeapNode(char c,double prob){
		left = right = NULL;
		this->source = c;
		this->prob = prob;
	}

	
};

//comparing two nodes

class compare{
public:	
	bool operator()(MinHeapNode* l ,MinHeapNode* r){
		return(l->prob > r->prob);
	}
};


//printing out the assigned code recursively

void printCodes(MinHeapNode* root,string str,multimap<double,int>* my_buffer,map<char,string> *print_values){
	if(!root){
		return;
	}

	if(root->source != '$'){
		print_values->insert(pair<char,string>(root->source,str));
		my_buffer->insert(pair<double,int>(root->prob,str.length()));
	}

	printCodes(root->left,str + "1",my_buffer,print_values);
	printCodes(root->right,str + "0",my_buffer,print_values);
}



//Main Huffman Builder

void HuffmanCodes(vector<char> source,vector<double> prob,multimap<double,int>* my_buffer){
	int size = source.size();
	MinHeapNode *left,*right,*top;

	//creating a min heap(priority queue)
	priority_queue<MinHeapNode* , vector<MinHeapNode*>,compare> minHeap;

	for(int i = 0;i<size;i++){
		minHeap.push(new MinHeapNode(source[i],prob[i]));
	}

	while (minHeap.size() != 1){
		//extract 2 min probabilty items

		left = minHeap.top();
		minHeap.pop();

		right = minHeap.top();
		minHeap.pop();

		//create a new node with probability as sum of the probabilities,
		//left and right will be two pointers assigned

		top = new MinHeapNode('$',left->prob + right->prob);

		top->left = left;
		top->right = right;
		minHeap.push(top);

	}

	map<char,string> print_values;
	printCodes(minHeap.top(),"",my_buffer,&print_values);

	cout << "\nThe Codes are" << endl;

	for(auto c : source){
		cout << c << ": " << print_values[c] << endl;  
	}


}


int main(){

	int num;
	vector<char> source;
	vector<double> probs;
	cout << "Enter Number of sources" << endl;
	cin >> num;

	cout << "Enter the name of the sources" << endl;
	for(int i = 0;i<num;i++){
		char a;
		cin >> a;
		source.push_back(a);
	}


	cout << "\nEnter their Probablities"<<endl;
	for(int i = 0;i<num;i++){
		double d;
		cin >> d;
		probs.push_back(d);
	}
	  
	cout << "\n";
	multimap<double,int> my_buffer;

	HuffmanCodes(source,probs,&my_buffer);


	//calculate efficiency 
	double h = 0.0;
	for (auto i : probs){
		h += (double)i*(log(1/(double)i)/log(2)) ;
	}

	double my_length = 0;
	for(auto i = my_buffer.begin(); i != my_buffer.end(); i++){
		my_length += (i->first )*(i->second);
		//cout << i->first <<" "<<i->second<<endl;
	}

	double efficiency = (double)h/my_length;

	cout << "\nThe efficiency of the algorithm is: " << efficiency*100 << "%"<<endl;
	cout <<"\nThe redundancy of the algorithm is: " <<  (1-efficiency)*100 << "%" << endl;
	return  0;

}
