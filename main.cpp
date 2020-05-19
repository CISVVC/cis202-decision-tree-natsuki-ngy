/*
   This program will create a decision tree for an animal
   guessing game.

   
   Pseudocode has been added as a hint to help with developing this
   program
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <ios>		//get stream size
#include <limits>	//get numeric size
#include "binary_tree.h"

Binary_tree read(istream& in)
{
    std::string line;
    std::string data;			//    declare data as string
    int level;				//    declare level as integer

    std::getline(in, line);		//    get line from stream and assign it to data

    int i = 0;
    while (!isalpha(line[i])) { i++; }	//    find data 

    int j = i - 1;
    while (isspace(line[j])) { j--; }	//    find level

    level = std::stoi(line.substr(0, j+1));

    if (level == -1)			//    if level == -1
        return Binary_tree();		//        return Binary_tree();

    data = line.substr(i);

    Binary_tree right = read(in);	//    declare left as a Binary_tree and assign it read(in)     Note:  it is a recursive call
    Binary_tree left = read(in); 	//    declare right as a Binary_tree and assign it to read(in)      Note:  it is a recursive call

    return Binary_tree(data, left, right);//    return Binary_tree(data, left, right)
}

void write(ostream& out, const Binary_tree& tree, int level)
{
    if (tree.empty())	 			//    if tree.empty()
    {
        out << -1 << "\n";			//        output -1 + \n to out
        return;					//        return 
    }

    out << level << " " << tree.data() << "\n";	//    output level + ' ' + tree.data() + \n to out

    write(out, tree.left(), level+1);		//    call write (out, tree.left(), level + 1)
    write(out, tree.right(), level+1);		//    call write (out, tree.right(), level + 1)
}

/*
 * helper function that will help with definite or indefinite 
 * articles in a string
 */
std::string article(const std::string& entry)
{
    std::string article = "a";
    if (std::string("aeiou").find(entry[0]) != std::string::npos)
    {
        article =  "an";
    }
    return article;
}

int main(int argc,char **argv)
{
    Binary_tree root;  
    // Strategy
    //  get the filename from the command line arguments
    //  open the file stream
    //  initialize the root Binary_tree variable with data from the 
    //  file stream to initialize the decision tree root by calling
    //  the read function
    //
    std::ifstream file(argv[1]);
    root = read(file); 
    file.close();

    Binary_tree question_tree = root;				// declare a Binary_tree question_tree and set it to root

    bool done = false;

    while(!done)							// while not done
    {
        std::string response;					//    declare a string called response
	std::string question;

        Binary_tree left = question_tree.left();		//    declare a Binary_tree called left and set it to question_tree.left()
        Binary_tree right = question_tree.right();		//    declare a Binary_tree called right and set it to question_tree.right()

        if (left.empty() && right.empty())			//    if left.empty() and right.empty()
	{
            std::cout << "Is it " << article(question_tree.data()) << " " << question_tree.data() << "? ";
	    std::cin >> response;				// get the response from the user and 

            if (response == "y")		// if it is correct,
                std::cout << "I guessed it!" << std::endl;	//     print  "I guessed it!"
	    else						// else
	    {
	        std::cout << "I give up. What is it? ";		//    print "I give up. What is it?"
		std::cin >> response;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            	std::cout << "Please give me a question that is true for "
		   << response << " and false for " 
		   << question_tree.data() << ". ";		//        print "Please give me a question that is true 
           							//                  for a hamster and false for a pig."
								//
	        std::getline(std::cin, question);		//        get the response from the user
            							//             example user response: Is it small and cuddly?  

	    //        Insert a node into question_tree so that this 
            //        question is used in future dialogs:
                question_tree.set(question, question_tree, Binary_tree(response));
            }

            //  Future dialog:
	    std::cout << "May I try again? ";			//     print "May I try again? "
	    std::cin >> response;				//     get response

            if (response == "y")				//     if response is yes
	    {
                question_tree = root;				//         question_tree = root
	    }
	    else						//     else
		done = true;
	}
        else							//  else
	{
            do							//      do
	    {
                std::cout << question_tree.data() << " ";		//        print Is it a question_tree.data()  (y/n): 
		std::cin >> response;				//        get response
	    } while((response != "y") && (response != "n"));	//      while (response != y and response != n)

            if (response == "y")				//      if response is y
                question_tree = left;				//         question_tree = left;
            else						//      else
		question_tree = right;				//         question_tree = right;
	}
    }

    // When done, write the decision tree to the data file by calling
    // the write function so that the new
    // question and answer is added to the data file
    std::ofstream out(argv[1]);
    write(out, root, 0);
    out.close();
}



