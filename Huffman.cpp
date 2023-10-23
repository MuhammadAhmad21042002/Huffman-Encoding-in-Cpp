#include<iostream>
#include<fstream>
#include<unistd.h>  
#include<vector>
#include<string>
#include <cmath>
#include <sstream>
#include <stdlib.h>
using namespace std;






struct node{   // For creating a huffman tree.
	

		double frequency;
		node* rightchild;
		node* leftchild;
		string value;
		string huffman_code;
};

class encode_class{
	
	
	
	public:
		
	    
		encode();
		
		
		
		
		
		
		node minHeap(vector<node> &heap_vector){  // This function finds the minimum node in the heap and return it.
	
	double temp_number = (double) INT_MAX;
	
	vector<node>::iterator iter1,temp_it;
	for(iter1  = heap_vector.begin();iter1!=heap_vector.end();iter1++){
		if(temp_number>(*iter1).frequency){
			
			temp_it = iter1;
			temp_number = (*iter1).frequency;
			
		}
	} 
	
	node temporary_node = (*temp_it);
	heap_vector.erase(temp_it);
	

	return temporary_node;
}

node Huffman_tree(vector<node> &heap_vector){  // This function is for building the binary tree.
	
	
	while(!heap_vector.empty()){
		node* temp = new node;
		node* child_1 = new node;
		node* child_2 = new node;
		*child_1 = minHeap(heap_vector); 
		*child_2 = minHeap(heap_vector);
		
		
		temp->leftchild = child_1;
		temp->rightchild=child_2;
		temp->frequency = child_1->frequency+child_2->frequency;
		heap_vector.push_back(*temp);
		if(heap_vector.size()==1){
			break;
		}
	}
	
	return heap_vector[0];
}


void tree_search(node* root_node,string s){/* In this function we traverse across the tree and assign '1'
                                              to the right node and assign '0' to the left node.*/
	
	node* temp_node = root_node;  
	
	temp_node->huffman_code = s;
	
	if(temp_node==NULL){
		return ;
	}
	
	else if(temp_node->leftchild==NULL && temp_node->rightchild==NULL){
//		cout<<"The value is : "<<temp_node->value<<endl;
//		cout<<"The frequency is : "<<temp_node->huffman_code<<endl;
		return ; 
	}
	
	else{
		temp_node->leftchild->huffman_code = s.append("0");
		s.erase(s.end()-1);
		
		temp_node->rightchild->huffman_code = s.append("1");
		s.erase(s.end()-1);
		
		tree_search(temp_node->leftchild,s.append("0"));
		s.erase(s.end()-1);
		tree_search(temp_node->rightchild,s.append("1"));
		s.erase(s.end()-1);
		
	}
	
}



node Huffman_code(vector<node> &heap_vector,string str){ // For getting the frequency of the words.
	
	
	

	
	
	vector<int> freq;   // Vector to store the frequencies of the values 
	vector<char> number;  // Vector to store the corresponding numbers to frequencies
	
	freq = gettingfrequency(str,number);  // This function will find the frequency of each word in the string and return it back.
	
//	cout<<"The number vector is : "<<endl;
//	for(int i=0;i<number.size();i++){
//		cout<<number[i]<<"  "<<freq[i]<<endl;
//	}
	    
	
	

	for(int i=0;i<number.size();i++){
		
		node tempnode;
		
		tempnode.value = number[i];
		tempnode.frequency = freq[i];
		tempnode.leftchild = NULL;
		tempnode.rightchild = NULL;
		heap_vector.push_back(tempnode);
		
	
	}

	node root = Huffman_tree(heap_vector);
	
	//node root;
	return root;
}

bool in_vector(vector<char> check_vector,char s ){  /* To check if a number is present in the vector or not. */
	
	int flag=0;
	for(int i=0;i<check_vector.size();i++){
		if(check_vector[i]==s){
			return 1;
		}
	}
	
	return 0;
}

int countingfrequency_words(char word_check,string b){//This function looks at a word and counts its frequency.
	
	int count=0;
	for(int i=0;i<b.size();i++){
		
		char temp = b[i];
		
		if(word_check==temp){
			count++;
		}
	}
	
	return count;
}


vector<int> gettingfrequency(string check,vector<char> &values){  // This function returns the frequency of the words typed.
	
	vector<int>  frequency_vector;
	
	for(int i=0;i<check.size();i++){
		
		char temp = check[i];
		
		if(!in_vector(values,temp))
		{
			int frequency_numbers=countingfrequency_words(temp,check);// To look at a specific word and counting its frequency.
			//cout<<"the frequency of  "<<temp<<"  is  : "<<frequency_numbers<<endl;
			values.push_back(temp);
			frequency_vector.push_back(frequency_numbers);
		}
	}
	
	return frequency_vector;
}

		
		



void dfs(node *root,string s,string &encode){   //  To look at a particular character in the string and convert it into huffman code.
	

	
	if(root->leftchild==NULL && root->rightchild==NULL){
		if(s == root->value){
			
			encode= root->huffman_code;
		}
	}
	
	else {
		dfs(root->leftchild,s,encode);
		dfs(root->rightchild,s,encode);
	}
	
	

}

string encode_values(node* root,string s){ // This funnction gets a string and the look up table, to encode that string.
	
	string encoded_binary;
	
	for(int i=0;i<s.size();i++){
		string temp(1,s[i]);
		string encoded_string;  // To assign the value to the string and return it using (by reference argument).
		
		dfs(root,temp,encoded_string);
		
		encoded_binary +=encoded_string; // Binary values to be returned.
	
	}
	
	
	
	return encoded_binary;
}






				
		
		
		
		
		
		
		
};



class bitChar{   /* This class is for writing to a binary file in the form of bits
as the normal approach writes to a file in the form of a byte. */
public:
    unsigned char* c;
    int shift_count;
    string BITS;

    bitChar()
    {
        shift_count = 0;
        c = (unsigned char*)calloc(1, sizeof(char));  // (calloc) allocates a block of memory for an array of objects and initializes all its bits to zero
    }

    string readByBits(ifstream& inf)
    {
        string s ="";
        char buffer[1];
        while (inf.read (buffer, 1))
        {   
        if(inf.eof())
        break;
            s += getBits(*buffer);
            
        }
        return s;
    }

    void setBITS(string X)
    {
        BITS = X;
    }

    int insertBits(ofstream& outf)
    {
        int total = 0;
        int key=0;
        while(BITS.length())
        {
            if(BITS[0] == '1')
                *c |= 1;   // Same as c=c|1, we are taking the or operation of c and 1
            *c <<= 1;
            
            ++shift_count;
            ++total;
            BITS.erase(0, 1);   // Deletes the value at index 0 specified by (0,1)
            
            if(BITS.size()==0){
            	key = 8-shift_count;
            	
				}
				
            if(shift_count == 7 )
            {
                if(BITS.size()>0)
                {
                    if(BITS[0] == '1')
                        *c |= 1;
                    ++total;
                    BITS.erase(0, 1);
                }
                
                writeBits(outf);
                shift_count = 0;
                free(c);
                c = (unsigned char*)calloc(1, sizeof(char));
                
            }
        }

        if(shift_count > 0)
        {  
             
            *c <<= (7 - shift_count);
            
            writeBits(outf);
            free(c);
            c = (unsigned char*)calloc(1, sizeof(char));
        }
        
        outf.put(key);
        outf.close();
        return total;
    }

    string getBits(unsigned char X)
    {
        stringstream itoa;
        for(unsigned s = 7; s > 0 ; s--)
        {
            itoa << ((X >> s) & 1);
        }
        
        itoa << (X&1) ;
        return itoa.str();
    }

    void writeBits(ofstream& outf)
    {
        outf << *c;
    }

    ~bitChar()
    {
        if(c)
            free(c);
    }
};

























string decode_to_original(node* root,string s){  // This function gets the encoded values and decodes them to their original values.
	
	if(root->leftchild==NULL && root->rightchild==NULL){
		
	}
	string decoded_string;
	int i=0;
	node* temp=root;
	while(s[i]!='\0'){  // Running the while loop until the end of the string.
		
	     temp=root;
		while(temp->leftchild!=NULL || temp->rightchild!=NULL){  // Running the while to reach the leaf nodes.
			
			if(s[i]=='0'){  
				temp=temp->leftchild;
			}
			
			
			else if(s[i]=='1'){
				temp=temp->rightchild;
			}
			
			 i++;  // going to the next value of the string as first value has already been decoded.
		}
		
		if(temp->rightchild==NULL &&temp->leftchild==NULL){ /* If both children are null, meaning it is a leaf node
		so storing it in a string.*/
			    
				decoded_string+=temp->value;
			}
		
		
	}
	
	return decoded_string;
}




string huffman_bits(string bits);






class file{
	public:
		
		encode_class e1;
		node root_node;
		
		
		
		void create_txt_file(string decoded_string){
			
			string file_name;
			label:  // goto condition
			
			cout<<"Enter the name of the txt file. Donot write the file extension..."<<endl;
			
			getline(cin,file_name);
			
			if(file_name.find(".")!=string::npos){
					cout<<"Donot enter the reserved word(.)";
					cout<<endl<<"Try again..."<<endl<<endl<<endl;
					goto label;
				}
			file_name+=".txt";   // Writing the extension of the file.
			
			ofstream new_file; 
			
			new_file.open(file_name.c_str(),ios::out | ios::trunc);	
			
			
			if(!new_file){
				
				cout<<endl<<endl;
				cout<<"There was an error opening this file..."<<endl;
				cout<<"Try again..."<<endl;
				cout<<endl<<endl<<endl;
			}
			
			else{
				new_file<<decoded_string;
				new_file.close();
				
				cout<<"File created successfully..."<<endl<<endl;
			}
			
			
				
			
		}
		void creating_zip_file(string encoded_string){  // This function creates a zip file.
		        
		        
		       
		        string zip_file_name;
		        
		        label:
		        cout<<"Enter the name of the zip file. Do not write the file extension. : "<<endl;
		        getline(cin,zip_file_name);
		        
		        
				if(zip_file_name.find(".") !=string::npos){  // string::npos basically means till the end of file.
					
					
					cout<<"Donot enter the reserved word(.)";
					cout<<endl<<"Try again..."<<endl<<endl<<endl;
					goto label;
				}
				   
		        zip_file_name+=".z";
		        
				ofstream this_file(zip_file_name.c_str(), ios::binary | ios::out);
    
    			bitChar bchar; // Calling the bitchar class.
    			bchar.setBITS(encoded_string);
    			bchar.insertBits(this_file);
    
   				 this_file.close();
   				 cout<<"File created successfully..."<<endl<<endl<<endl;
   			     return;
		}
		
		
		
		
		
		void encoding_txt_file(string to_be_encoded){  // This function encodes the string values.
			
			
			vector<node> node_vector;
           
           
 
          
          root_node = e1.Huffman_code(node_vector,to_be_encoded);
          e1.tree_search(&root_node,""); // This function assigns the binary values to the tree nodes.
          
    
    
    
	    
	    string encoded = e1.encode_values(&root_node,to_be_encoded); /* Calling the function of 
		encode class, to encode the values*/
		
     	
		
		
		creating_zip_file(encoded);  // Calling the function to create a zip file.
		
		
     	        
	    //cout<<endl<<"The encoded string is : "<<encoded<<endl;
	    
	    
	    
		}
		
		
		void get_file_for_encoding(string final_string){               /* Function for encoding the file.
		It is 1 of the 3 functions for encoding the file. This function opens the .txt file and store the values in a 
		string. The function above this function encodes the value of the text material. The function above that
		 function stores the encoded values in an encoded file.   */
		
		    
			    
                encoding_txt_file(final_string);
		}
		
		
		
		
		
		
		
		void decode(string zip_file_name){  // Function for decoding the file.
			
			
			//cout<<zip_file_name<<endl;
			
			
			string final_string;
			string final_encoded_bits;
			string encoded;
			
			ifstream new_file(zip_file_name.c_str());
   				
   				if(!new_file){
   					cout<<endl<<endl<<endl;
   					cout<<"There was an error opening this file...  "<<endl;
					cout<<"Try again..."<<endl;
					cout<<endl<<endl<<endl<<endl;
				   }
				else{
					cout<<"File"<<zip_file_name<<" opened successfully..."<<endl<<endl<<endl;
					
					bitChar bchar;  // Calling the bitchar class.
					
					encoded = bchar.readByBits(new_file);
				    
			        final_encoded_bits = huffman_bits(encoded);  /* As we are writing and reading to a binary file in the form  bits instead of bytes. The bits are stored
					in a variable which is of a byte size. If the byte is completed it is flushed into the file but in the end sometimes some bits remain and we pad them by adding
					0's at the end to complete a byte. As these bits are unnecessary bits and are not required by us so we need to find a way to get and rid of them. That is 
					why we are using this function.*/
					
					
				   new_file.close();
					
					
					
				}
				
				//node temp_node = root_node;
				//cout<<"final encoded bits are : "<<final_encoded_bits<<endl;
				
				string decoded = decode_to_original(&root_node,final_encoded_bits);  // Calling the function to decode the file.
     	       
   				cout<<"decoded string is: "<<decoded<<endl;
   				string answer;
   				cout<<endl<<endl<<endl;
				cout<<"Would you like to store it in a (.txt) file.\n'Press y for yes Or else any number'"<<endl;
				cin>>answer;
				cin.ignore();
				if(answer=="y" || answer=="Y"){
					create_txt_file(decoded);
				}
		}
};









int convert(long long n) {
  int dec = 0, i = 0, rem;

  while (n!=0) {
    rem = n % 10;
    n /= 10;
    dec += rem * pow(2, i);
    ++i;
  }

  return dec;
}


string huffman_bits(string bits)  /* This code is for getting the decoded bits from huffman encoded file and separate the 
 huffman encoded bits.*/
{
	string huffman_code;
	// The total bits extracted from the binary file.
	int code_size = bits.size()-8;
	
	
	
	
	for(int i=0;i<code_size;i++){ // This separates the huffman bits from the last byte which stores the information about the actual huffman bits.
		huffman_code+=bits[i];
	}
	
	string extra_bits;
	for(int i=code_size;i<bits.size();i++){ // This extracts the last byte of the data to decode a huffman file.
		extra_bits+=bits[i];
	}
	
	int eb = atoi(extra_bits.data());
	
	int returned = convert(eb);  // This finds the decimal equivalent of the binary number stored at the end of the file to return the actual huffman code.
	
	
	string return_string;// This is the real huffman code which is extracted from the string.
	for(int i=0;i<code_size-returned;i++){
		return_string+=huffman_code[i];
	}

	
	return return_string;
	
}




















int main(){
	
	
	
	
    
    file f1;
    string option;
    
   
    while(1){
	
    cout<<"Enter the option : "<<endl;
    cout<<"1. Encode file"<<endl;
    cout<<"2. Enter a paragraph and store it into (.z) and (.txt) files"<<endl;
    cout<<"3. Exit()"<<endl;
    cin>>option;
    
    
    
    if(option=="1")
    {
    	cin.ignore();
    	
    	new_label:
    	string file_name;
    	cout<<"Enter the file name to be encoded. Donot write the file extension. : "<<endl;
    	
    	getline(cin,file_name);
    	file_name+=".txt";
    	
    	
    	
    	
    	
    	
    	
    	
    	
    	string final_string;                                            
		fstream file;
		string read;
	
		file.open(file_name.c_str(),ios::in);  
		
		if(!file)
		{
		    cout<<endl<<endl<<endl;
   			cout<<"There was an error opening this file...  "<<endl;
			cout<<"Please Try again..."<<endl;
			
		 goto new_label;
			cout<<endl<<endl<<endl<<endl;
			}
			
			
			else
			{
				cout<<"File  "<<file_name<<" opened successfully..."<<endl<<endl<<endl;
				while(file){
				getline(file,read);  // Since getline reads till the end of the file. That is adding '\n'
				final_string+=read+"\n"; 
						
				if (file.eof())
				break;
				}
				
	
	
			file.close();
            f1.get_file_for_encoding(final_string);
   
           			
           
           			
                    
           }
    	
    	string opt;
        cout<<"\t\t\t Want to decode the file : (Press 1) |(Else Press any key) " ;
        cin>>opt;
        
        if(opt=="1"){
        
			
        string zip_file_name;
		cout<<"Enter the name of the file to be decoded. Donot write the file extension. : "<<endl;
		cin.ignore();
		getline(cin,zip_file_name);
		zip_file_name+=".z";
    	f1.decode(zip_file_name);
        	
        	
        }
        
    	continue;
	}
    
    
    
    
    
    else if(option=="2"){
    	
    	
    	string paragraph;
    	cout<<"Enter the paragraph : "<<endl;
    	cin.ignore();
    	getline(cin,paragraph);
    	
    	cout<<endl<<endl<<endl;
    	f1.get_file_for_encoding(paragraph);
        cout<<endl<<endl<<endl;
    	f1.create_txt_file(paragraph);
    	
    	
    	string opt;
        cout<<"\t\t\t Want to decode the encoded file again : (Press 1) |(Else Press any key) " ;
        cin>>opt;
        
        if(opt=="1"){
        
			
        string zip_file_name;
		cout<<"Enter the name of the file to be decoded. Donot write the file extension. : "<<endl;
		cin.ignore();
		getline(cin,zip_file_name);
		zip_file_name+=".z";
    	f1.decode(zip_file_name);
        	
        	
        }
        
        
    	continue;
	}
	

    else if(option=="3"){
    	cout<<endl<<endl<<"\t________________________________Thank you for visiting________________________________"<<endl<<endl<<endl;
    	break;
	}
    
    else{
    	cout<<endl<<endl<<"You entered the wrong key. Please try again..."<<endl;
    	sleep(1);
    	system("cls");
    	continue;
	}
    }
    return 0;
}

















