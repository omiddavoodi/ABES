#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

struct flags
{
	bool greater;
	bool equal;
	
};

flags p_Flags;
int **vars;
int numvars = 0;
vector<int*> p_Stack;
int stack_top = -1;

void show_vars()
{
     for (int i = 0; i < numvars; ++i)
     {
         cout << *vars[i] << endl;
     }
}

void interpret(string program)
{
	p_Flags.greater = 0;
	p_Flags.equal = 0;
	
	
	//cout << program;
    if (program.substr(0,4) == "AIHO")
    {
        
		int * headerLen = new int;
        string headerLenS = program.substr(4,4);
        for (int i = 0; i < 4; ++i)
        {
            ((char*)headerLen)[i] = headerLenS[i];
        }
        
		int * codeLen = new int;
        string codeLenS = program.substr(8,4);
        for (int i = 0; i < 4; ++i)
        {
            ((char*)codeLen)[i] = codeLenS[i];
        }
        
        
        numvars = (*headerLen)/4 - 2;
        vars = new int*[numvars];
        for (int i = 0; i < numvars; ++i)
        {
            int * temp = new int;
            string varsS = program.substr((3+i)*4,4);
            for (int j = 0; j < 4; ++j)
            {
                ((char*)temp)[j] = varsS[j];
            }
            
            vars[i] = temp;
            
            //cout << *vars[i] << endl;
        }
		//cout << *codeLen << endl;
        
        string codeS = program.substr((3+numvars)*4,*codeLen);
        
        int program_pointer = 0;
        
        while (program_pointer < *codeLen)
        {
            //cout << codeS[program_pointer] << endl;
            if (codeS[program_pointer] == 'f')
            {
                program_pointer += 1;
                short* varPoint = new short;

                *((char*)varPoint) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint + 1) = codeS[program_pointer];
                program_pointer += 1;
                
                for (int i = 0; i < 4; ++i)
                {
                    ((char*)p_Stack[stack_top - *varPoint])[i] = codeS[i+program_pointer];
                }
                
                program_pointer += 4;
				
				delete varPoint;
                
            }
            else if (codeS[program_pointer] == 'e')
            {
                program_pointer += 1;
                short* varPoint = new short;
                *((char*)varPoint) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint + 1) = codeS[program_pointer];
                program_pointer += 1;
                short* varPoint2 = new short;
                *((char*)varPoint2) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint2 + 1) = codeS[program_pointer];
                program_pointer += 1;
				
				for (int i = 0; i < 4; ++i)
                {
                    ((char*)p_Stack[stack_top - *varPoint])[i] = ((char*)p_Stack[stack_top - *varPoint2])[i];
                }
				
				delete varPoint;
				delete varPoint2;
            }
			
			else if (codeS[program_pointer] == 'E')
            {
                program_pointer += 1;
                int* varPoint2 = new int;
                *((char*)varPoint2) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint2 + 1) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint2 + 2) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint2 + 3) = codeS[program_pointer];
                program_pointer += 1;
				
				/*for (int i = 0; i < 4; ++i)
                {
                    ((char*)vars[*varPoint])[i] = ((char*)vars[*varPoint2])[i];
                }*/
				
				++stack_top;
				p_Stack.push_back(varPoint2);
				
            }
			else if (codeS[program_pointer] == 'F')
            {
                program_pointer += 1;
                int* varPoint2 = new int;
                *((char*)varPoint2) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint2 + 1) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint2 + 2) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint2 + 3) = codeS[program_pointer];
                program_pointer += 1;
				
				/*for (int i = 0; i < 4; ++i)
                {
                    ((char*)vars[*varPoint])[i] = ((char*)vars[*varPoint2])[i];
                }*/
				
				while (*varPoint2 > 0)
				{
					int *temp = p_Stack[stack_top];
					--(*varPoint2);
					--stack_top;
					p_Stack.pop_back();
					delete temp;
				}

				delete varPoint2;
				
            }
			else if (codeS[program_pointer] == 'a')
            {
                program_pointer += 1;
                short* varPoint = new short;
                *((char*)varPoint) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint + 1) = codeS[program_pointer];
                program_pointer += 1;
                short* varPoint2 = new short;
                *((char*)varPoint2) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint2 + 1) = codeS[program_pointer];
                program_pointer += 1;
				
                *(p_Stack[stack_top - *varPoint]) += *(p_Stack[stack_top - *varPoint2]);

				delete varPoint;
				delete varPoint2;
            }
            else if (codeS[program_pointer] == 'A')
            {
                program_pointer += 1;
                short* varPoint = new short;
                *((char*)varPoint) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint + 1) = codeS[program_pointer];
                program_pointer += 1;
                int* varPoint2 = new int;
                *((char*)varPoint2) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint2 + 1) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint2 + 2) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint2 + 3) = codeS[program_pointer];
                program_pointer += 1;
				
                *(p_Stack[stack_top - *varPoint]) += *varPoint2;

				delete varPoint;
				delete varPoint2;
            }
			else if (codeS[program_pointer] == 'b')
            {
                program_pointer += 1;
                short* varPoint = new short;
                *((char*)varPoint) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint + 1) = codeS[program_pointer];
                program_pointer += 1;
                short* varPoint2 = new short;
                *((char*)varPoint2) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint2 + 1) = codeS[program_pointer];
                program_pointer += 1;
				
				*(p_Stack[stack_top - *varPoint]) -= *(p_Stack[stack_top - *varPoint2]);
				//show_vars();
				delete varPoint;
				delete varPoint2;
            }
			else if (codeS[program_pointer] == 'B')
            {
                program_pointer += 1;
                short* varPoint = new short;
                *((char*)varPoint) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint + 1) = codeS[program_pointer];
                program_pointer += 1;
                int* varPoint2 = new int;
                *((char*)varPoint2) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint2 + 1) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint2 + 2) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint2 + 3) = codeS[program_pointer];
                program_pointer += 1;
				
                *(p_Stack[stack_top - *varPoint]) -= *varPoint2;

				delete varPoint;
				delete varPoint2;
            }
			else if (codeS[program_pointer] == 'c')
            {
                program_pointer += 1;
                short* varPoint = new short;
                *((char*)varPoint) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint + 1) = codeS[program_pointer];
                program_pointer += 1;
                short* varPoint2 = new short;
                *((char*)varPoint2) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint2 + 1) = codeS[program_pointer];
                program_pointer += 1;
				
                *(p_Stack[stack_top - *varPoint]) *= *(p_Stack[stack_top - *varPoint2]);
				//show_vars();
				delete varPoint;
				delete varPoint2;
            }
			else if (codeS[program_pointer] == 'C')
            {
                program_pointer += 1;
                short* varPoint = new short;
                *((char*)varPoint) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint + 1) = codeS[program_pointer];
                program_pointer += 1;
                int* varPoint2 = new int;
                *((char*)varPoint2) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint2 + 1) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint2 + 2) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint2 + 3) = codeS[program_pointer];
                program_pointer += 1;
				
                *(p_Stack[stack_top - *varPoint]) *= *varPoint2;

				delete varPoint;
				delete varPoint2;
            }
			else if (codeS[program_pointer] == 'd')
            {
                program_pointer += 1;
                short* varPoint = new short;
                *((char*)varPoint) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint + 1) = codeS[program_pointer];
                program_pointer += 1;
                short* varPoint2 = new short;
                *((char*)varPoint2) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint2 + 1) = codeS[program_pointer];
                program_pointer += 1;
				
				*(p_Stack[stack_top - *varPoint]) /= *(p_Stack[stack_top - *varPoint2]);
				//show_vars();
				delete varPoint;
				delete varPoint2;
            }
			else if (codeS[program_pointer] == 'D')
            {
                program_pointer += 1;
                short* varPoint = new short;
                *((char*)varPoint) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint + 1) = codeS[program_pointer];
                program_pointer += 1;
                int* varPoint2 = new int;
                *((char*)varPoint2) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint2 + 1) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint2 + 2) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint2 + 3) = codeS[program_pointer];
                program_pointer += 1;
				
                *(p_Stack[stack_top - *varPoint]) /= *varPoint2;

				delete varPoint;
				delete varPoint2;
            }
			else if (codeS[program_pointer] == 'r')
            {
                program_pointer += 1;
                short* varPoint = new short;
                *((char*)varPoint) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint + 1) = codeS[program_pointer];
                program_pointer += 1;
                short* varPoint2 = new short;
                *((char*)varPoint2) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint2 + 1) = codeS[program_pointer];
                program_pointer += 1;
				
				*(p_Stack[stack_top - *varPoint]) = (*(p_Stack[stack_top - *varPoint]) < *(p_Stack[stack_top - *varPoint2])) ? 1 : 0;
				
				//show_vars();
				delete varPoint;
				delete varPoint2;
            }
			else if (codeS[program_pointer] == 'R')
            {
                program_pointer += 1;
                short* varPoint = new short;
                *((char*)varPoint) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint + 1) = codeS[program_pointer];
                program_pointer += 1;
                int* varPoint2 = new int;
                *((char*)varPoint2) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint2 + 1) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint2 + 2) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint2 + 3) = codeS[program_pointer];
                program_pointer += 1;
				
				*(p_Stack[stack_top - *varPoint]) = (*(p_Stack[stack_top - *varPoint]) < *varPoint2) ? 1 : 0;

				delete varPoint;
				delete varPoint2;
            }
			else if (codeS[program_pointer] == 'u')
            {
                program_pointer += 1;
                short* varPoint = new short;
                *((char*)varPoint) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint + 1) = codeS[program_pointer];
                program_pointer += 1;
                short* varPoint2 = new short;
                *((char*)varPoint2) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint2 + 1) = codeS[program_pointer];
                program_pointer += 1;
				
				*(p_Stack[stack_top - *varPoint]) = (*(p_Stack[stack_top - *varPoint]) <= *(p_Stack[stack_top - *varPoint2])) ? 1 : 0;
				
				//show_vars();
				delete varPoint;
				delete varPoint2;
            }
			else if (codeS[program_pointer] == 'U')
            {
                program_pointer += 1;
                short* varPoint = new short;
                *((char*)varPoint) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint + 1) = codeS[program_pointer];
                program_pointer += 1;
                int* varPoint2 = new int;
                *((char*)varPoint2) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint2 + 1) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint2 + 2) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint2 + 3) = codeS[program_pointer];
                program_pointer += 1;
				
				*(p_Stack[stack_top - *varPoint]) = (*(p_Stack[stack_top - *varPoint]) <= *varPoint2) ? 1 : 0;

				delete varPoint;
				delete varPoint2;
            }
			else if (codeS[program_pointer] == 's')
            {
                program_pointer += 1;
                short* varPoint = new short;
                *((char*)varPoint) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint + 1) = codeS[program_pointer];
                program_pointer += 1;
                short* varPoint2 = new short;
                *((char*)varPoint2) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint2 + 1) = codeS[program_pointer];
                program_pointer += 1;
				
				*(p_Stack[stack_top - *varPoint]) = (*(p_Stack[stack_top - *varPoint]) > *(p_Stack[stack_top - *varPoint2])) ? 1 : 0;
				
				//show_vars();
				delete varPoint;
				delete varPoint2;
            }
			else if (codeS[program_pointer] == 'S')
            {
                program_pointer += 1;
                short* varPoint = new short;
                *((char*)varPoint) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint + 1) = codeS[program_pointer];
                program_pointer += 1;
                int* varPoint2 = new int;
                *((char*)varPoint2) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint2 + 1) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint2 + 2) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint2 + 3) = codeS[program_pointer];
                program_pointer += 1;
				
				*(p_Stack[stack_top - *varPoint]) = (*(p_Stack[stack_top - *varPoint]) > *varPoint2) ? 1 : 0;

				delete varPoint;
				delete varPoint2;
            }
			else if (codeS[program_pointer] == '1')
            {
                program_pointer += 1;
                short* varPoint = new short;
                *((char*)varPoint) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint + 1) = codeS[program_pointer];
                program_pointer += 1;
                short* varPoint2 = new short;
                *((char*)varPoint2) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint2 + 1) = codeS[program_pointer];
                program_pointer += 1;
				
				*(p_Stack[stack_top - *varPoint]) = (*(p_Stack[stack_top - *varPoint]) != *(p_Stack[stack_top - *varPoint2])) ? 1 : 0;
				
				//show_vars();
				delete varPoint;
				delete varPoint2;
            }
			else if (codeS[program_pointer] == '2')
            {
                program_pointer += 1;
                short* varPoint = new short;
                *((char*)varPoint) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint + 1) = codeS[program_pointer];
                program_pointer += 1;
                int* varPoint2 = new int;
                *((char*)varPoint2) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint2 + 1) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint2 + 2) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint2 + 3) = codeS[program_pointer];
                program_pointer += 1;
				
				*(p_Stack[stack_top - *varPoint]) = (*(p_Stack[stack_top - *varPoint]) != *varPoint2) ? 1 : 0;

				delete varPoint;
				delete varPoint2;
            }
			else if (codeS[program_pointer] == '3')
            {
                program_pointer += 1;
                short* varPoint = new short;
                *((char*)varPoint) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint + 1) = codeS[program_pointer];
                program_pointer += 1;
                short* varPoint2 = new short;
                *((char*)varPoint2) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint2 + 1) = codeS[program_pointer];
                program_pointer += 1;
				
				*(p_Stack[stack_top - *varPoint]) = (*(p_Stack[stack_top - *varPoint]) == *(p_Stack[stack_top - *varPoint2])) ? 1 : 0;
				
				//show_vars();
				delete varPoint;
				delete varPoint2;
            }
			else if (codeS[program_pointer] == '4')
            {
                program_pointer += 1;
                short* varPoint = new short;
                *((char*)varPoint) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint + 1) = codeS[program_pointer];
                program_pointer += 1;
                int* varPoint2 = new int;
                *((char*)varPoint2) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint2 + 1) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint2 + 2) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint2 + 3) = codeS[program_pointer];
                program_pointer += 1;
				
				*(p_Stack[stack_top - *varPoint]) = (*(p_Stack[stack_top - *varPoint]) == *varPoint2) ? 1 : 0;

				delete varPoint;
				delete varPoint2;
            }
			else if (codeS[program_pointer] == 'v')
            {
                program_pointer += 1;
                short* varPoint = new short;
                *((char*)varPoint) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint + 1) = codeS[program_pointer];
                program_pointer += 1;
                short* varPoint2 = new short;
                *((char*)varPoint2) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint2 + 1) = codeS[program_pointer];
                program_pointer += 1;
				
				*(p_Stack[stack_top - *varPoint]) = (*(p_Stack[stack_top - *varPoint]) >= *(p_Stack[stack_top - *varPoint2])) ? 1 : 0;
				
				//show_vars();
				delete varPoint;
				delete varPoint2;
            }
			else if (codeS[program_pointer] == 'V')
            {
                program_pointer += 1;
                short* varPoint = new short;
                *((char*)varPoint) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint + 1) = codeS[program_pointer];
                program_pointer += 1;
                int* varPoint2 = new int;
                *((char*)varPoint2) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint2 + 1) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint2 + 2) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint2 + 3) = codeS[program_pointer];
                program_pointer += 1;
				
				*(p_Stack[stack_top - *varPoint]) = (*(p_Stack[stack_top - *varPoint]) >= *varPoint2) ? 1 : 0;

				delete varPoint;
				delete varPoint2;
            }
			else if (codeS[program_pointer] == 'g')
            {
                program_pointer += 1;
                short* varPoint = new short;
                *((char*)varPoint) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint + 1) = codeS[program_pointer];
                program_pointer += 1;
                short* varPoint2 = new short;
                *((char*)varPoint2) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint2 + 1) = codeS[program_pointer];
                program_pointer += 1;
				
				int res = *(p_Stack[stack_top - *varPoint]) - *(p_Stack[stack_top - *varPoint2]);
				
				p_Flags.greater = 0;
				p_Flags.equal = 0;
				if (res > 0)
					p_Flags.greater = 1;
				else if (res == 0)
					p_Flags.equal = 1;
				//show_vars();
				delete varPoint;
				delete varPoint2;
            }
			else if (codeS[program_pointer] == 'G')
            {
                program_pointer += 1;
                short* varPoint = new short;
                *((char*)varPoint) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint + 1) = codeS[program_pointer];
                program_pointer += 1;
                int* varPoint2 = new int;
                *((char*)varPoint2) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint2 + 1) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint2 + 2) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint2 + 3) = codeS[program_pointer];
                program_pointer += 1;
				
                int res = *(p_Stack[stack_top - *varPoint]) - *varPoint2;
				
				p_Flags.greater = 0;
				p_Flags.equal = 0;
				if (res > 0)
					p_Flags.greater = 1;
				else if (res == 0)
					p_Flags.equal = 1;
				//show_vars();
				delete varPoint;
				delete varPoint2;
            }
			else if (codeS[program_pointer] == '5')
            {
				
				int* addr = new int;
                program_pointer += 1;
                *((char*)addr) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)addr + 1) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)addr + 2) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)addr + 3) = codeS[program_pointer];
                program_pointer += 1;
				
				int* oldaddr = new int;
				*oldaddr = program_pointer;
				p_Stack.push_back(oldaddr);
				++stack_top;

				/*cout << "       Call      " << endl;
				cout << "--- Top of stack ---" << endl;

				cout << "| Return address: " << *(p_Stack[stack_top]) << endl;
				if (stack_top - 3 >= 0)
				{
					cout << "| Parameter 1: " << *(p_Stack[stack_top - 2]) << endl;
					cout << "| Return value location: " << *(p_Stack[stack_top - 1]) << endl;
				}
				else
				{
					cout << "| Parameter 1: " << *(p_Stack[stack_top - 1]) << endl;
				}
				cout << "--- Rest of stack ---" << endl;
				for (int j = p_Stack.size() - 4; j >= 0; --j)
				{
					cout << "|      " << *(p_Stack[j]) << endl;
				}

				cout << "--- End of stack ---" << endl;*/
				//testsalam
				program_pointer = *addr;
				//show_vars();
				delete addr;
            }
			else if (codeS[program_pointer] == '6')
            {
				int* oldaddr = p_Stack[stack_top];
				program_pointer = *oldaddr;
				p_Stack.pop_back();
				--stack_top;

				//show_vars();
				delete oldaddr;
            }
			else if (codeS[program_pointer] == '7')
            {
                program_pointer += 1;
                short* varPoint = new short;
                *((char*)varPoint) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint + 1) = codeS[program_pointer];
                program_pointer += 1;
                short* varPoint2 = new short;
                *((char*)varPoint2) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint2 + 1) = codeS[program_pointer];
                program_pointer += 1;
				
				int res = *(p_Stack[stack_top - *varPoint]) - *(p_Stack[stack_top - *varPoint2]);
				
				p_Flags.greater = 0;
				p_Flags.equal = 0;
				if (res > 0)
					p_Flags.greater = 1;
				else if (res == 0)
					p_Flags.equal = 1;
				//show_vars();
				delete varPoint;
				delete varPoint2;

				int* oldaddr = p_Stack[stack_top];
				program_pointer = *oldaddr;
				p_Stack.pop_back();
				--stack_top;

				//show_vars();
				delete oldaddr;
            }
			else if (codeS[program_pointer] == '8')
            {
                program_pointer += 1;
                short* varPoint = new short;
                *((char*)varPoint) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint + 1) = codeS[program_pointer];
                program_pointer += 1;
                int* varPoint2 = new int;
                *((char*)varPoint2) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint2 + 1) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint2 + 2) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint2 + 3) = codeS[program_pointer];
                program_pointer += 1;
				
                int res = *(p_Stack[stack_top - *varPoint]) - *varPoint2;
				
				p_Flags.greater = 0;
				p_Flags.equal = 0;
				if (res > 0)
					p_Flags.greater = 1;
				else if (res == 0)
					p_Flags.equal = 1;
				//show_vars();
				delete varPoint;
				delete varPoint2;

				int* oldaddr = p_Stack[stack_top];
				p_Stack.pop_back();
				--stack_top;

				//show_vars();
				delete oldaddr;
            }
			else if (codeS[program_pointer] == 'h')
            {
				int* addr = new int;
                program_pointer += 1;
                *((char*)addr) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)addr + 1) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)addr + 2) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)addr + 3) = codeS[program_pointer];
                program_pointer += 1;
				
				if (!p_Flags.greater && !p_Flags.equal)
					program_pointer = *addr;
				//show_vars();
				delete addr;
            }
			else if (codeS[program_pointer] == 'i')
            {
				int* addr = new int;
                program_pointer += 1;
                *((char*)addr) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)addr + 1) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)addr + 2) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)addr + 3) = codeS[program_pointer];
                program_pointer += 1;
				
				if (p_Flags.greater && !p_Flags.equal)
					program_pointer = *addr;
				//show_vars();
				delete addr;
            }
			else if (codeS[program_pointer] == 'j')
            {
				int* addr = new int;
                program_pointer += 1;
                *((char*)addr) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)addr + 1) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)addr + 2) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)addr + 3) = codeS[program_pointer];
                program_pointer += 1;
				
				if (!p_Flags.greater || p_Flags.equal)
					program_pointer = *addr;
				//show_vars();
				delete addr;
            }
			else if (codeS[program_pointer] == 'k')
            {
				int* addr = new int;
                program_pointer += 1;
                *((char*)addr) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)addr + 1) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)addr + 2) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)addr + 3) = codeS[program_pointer];
                program_pointer += 1;
				
				if (p_Flags.greater || p_Flags.equal)
					program_pointer = *addr;
				//show_vars();
				delete addr;
            }
			else if (codeS[program_pointer] == 'l')
            {
				int* addr = new int;
                program_pointer += 1;
                *((char*)addr) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)addr + 1) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)addr + 2) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)addr + 3) = codeS[program_pointer];
                program_pointer += 1;
				
				if (p_Flags.equal)
					program_pointer = *addr;
				//show_vars();
				delete addr;
            }
			else if (codeS[program_pointer] == 'm')
            {
				int* addr = new int;
                program_pointer += 1;
                *((char*)addr) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)addr + 1) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)addr + 2) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)addr + 3) = codeS[program_pointer];
                program_pointer += 1;
				
				if (!p_Flags.equal)
					program_pointer = *addr;
				//show_vars();
				delete addr;
            }
			else if (codeS[program_pointer] == 'n')
            {
                program_pointer += 1;
                short* varPoint = new short;
                *((char*)varPoint) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint + 1) = codeS[program_pointer];
                program_pointer += 1;
                short* varPoint2 = new short;
                *((char*)varPoint2) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint2 + 1) = codeS[program_pointer];
                program_pointer += 1;
				
				*(p_Stack[stack_top - *varPoint]) &= *(p_Stack[stack_top - *varPoint2]);
				//show_vars();
				delete varPoint;
				delete varPoint2;
            }
			else if (codeS[program_pointer] == 'N')
            {
                program_pointer += 1;
                short* varPoint = new short;
                *((char*)varPoint) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint + 1) = codeS[program_pointer];
                program_pointer += 1;
                int* varPoint2 = new int;
                *((char*)varPoint2) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint2 + 1) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint2 + 2) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint2 + 3) = codeS[program_pointer];
                program_pointer += 1;
				
				*(p_Stack[stack_top - *varPoint]) &= *varPoint2;
				//show_vars();
				delete varPoint;
				delete varPoint2;
            }
			else if (codeS[program_pointer] == 'o')
            {
                program_pointer += 1;
                short* varPoint = new short;
                *((char*)varPoint) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint + 1) = codeS[program_pointer];
                program_pointer += 1;
                short* varPoint2 = new short;
                *((char*)varPoint2) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint2 + 1) = codeS[program_pointer];
                program_pointer += 1;
				
				*(p_Stack[stack_top - *varPoint]) |= *(p_Stack[stack_top - *varPoint2]);
				//show_vars();
				delete varPoint;
				delete varPoint2;
            }
			else if (codeS[program_pointer] == 'O')
            {
                program_pointer += 1;
                short* varPoint = new short;
                *((char*)varPoint) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint + 1) = codeS[program_pointer];
                program_pointer += 1;
                int* varPoint2 = new int;
                *((char*)varPoint2) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint2 + 1) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint2 + 2) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint2 + 3) = codeS[program_pointer];
                program_pointer += 1;
				
				*(p_Stack[stack_top - *varPoint]) |= *varPoint2;
				//show_vars();
				delete varPoint;
				delete varPoint2;
            }
			else if (codeS[program_pointer] == 'p')
            {
                program_pointer += 1;
                short* varPoint = new short;
                *((char*)varPoint) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint + 1) = codeS[program_pointer];
                program_pointer += 1;
                short* varPoint2 = new short;
                *((char*)varPoint2) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint2 + 1) = codeS[program_pointer];
                program_pointer += 1;
				
				*(p_Stack[stack_top - *varPoint]) ^= *(p_Stack[stack_top - *varPoint2]);
				//show_vars();
				delete varPoint;
				delete varPoint2;
            }
			else if (codeS[program_pointer] == 'P')
            {
                program_pointer += 1;
                short* varPoint = new short;
                *((char*)varPoint) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint + 1) = codeS[program_pointer];
                program_pointer += 1;
                int* varPoint2 = new int;
                *((char*)varPoint2) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint2 + 1) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint2 + 2) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint2 + 3) = codeS[program_pointer];
                program_pointer += 1;
				
				*(p_Stack[stack_top - *varPoint]) ^= *varPoint2;
				//show_vars();
				delete varPoint;
				delete varPoint2;
            }
			else if (codeS[program_pointer] == 'q')
            {
                program_pointer += 1;
                short* varPoint = new short;
                *((char*)varPoint) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint + 1) = codeS[program_pointer];
                program_pointer += 1;
				
				*(p_Stack[stack_top - *varPoint]) = !(*(p_Stack[stack_top - *varPoint]));
				//show_vars();
				delete varPoint;
            }
            else if (codeS[program_pointer] == 't')
            {
                program_pointer += 1;
                short* varPoint = new short;
                *((char*)varPoint) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint + 1) = codeS[program_pointer];
                program_pointer += 1;
                short* varPoint2 = new short;
                *((char*)varPoint2) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint2 + 1) = codeS[program_pointer];
                program_pointer += 1;
				
				*(p_Stack[stack_top - *varPoint]) %= *(p_Stack[stack_top - *varPoint2]);
				//show_vars();
				delete varPoint;
				delete varPoint2;
            }
			else if (codeS[program_pointer] == 'T')
            {
                program_pointer += 1;
                short* varPoint = new short;
                *((char*)varPoint) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint + 1) = codeS[program_pointer];
                program_pointer += 1;
                int* varPoint2 = new int;
                *((char*)varPoint2) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint2 + 1) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint2 + 2) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint2 + 3) = codeS[program_pointer];
                program_pointer += 1;
				
				*(p_Stack[stack_top - *varPoint]) %= *varPoint2;
				//show_vars();
				delete varPoint;
				delete varPoint2;
            }
            else if (codeS[program_pointer] == 'x')
            {
				int* addr = new int;
                program_pointer += 1;
                *((char*)addr) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)addr + 1) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)addr + 2) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)addr + 3) = codeS[program_pointer];
                //program_pointer += 1;
				
				
				program_pointer = *addr;
				//show_vars();
				delete addr;
            }
            else if (codeS[program_pointer] == 'y')
            {
                program_pointer += 1;
				short* varPoint = new short;
                *((char*)varPoint) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint + 1) = codeS[program_pointer];
                program_pointer += 1;
				
				cout << *(p_Stack[stack_top - *varPoint]) << endl;
				
				delete varPoint;
            }
			else if (codeS[program_pointer] == 'z')
            {
                //cout << "XXXX";
                program_pointer += 1;
				short* varPoint = new short;
                *((char*)varPoint) = codeS[program_pointer];
                program_pointer += 1;
                *((char*)varPoint + 1) = codeS[program_pointer];
                program_pointer += 1;
				
				int temp;
				cin >> temp;
				*(p_Stack[stack_top - *varPoint]) = temp;
				
				delete varPoint;
            }
            else
            {
                program_pointer += 1;
            }
        }
        //show_vars();
        //cout << codeS;
        
    }
    //cout << "Done";
}


int main(int argc, char *argv[])
{
    
    if (argc > 1)
    {
        //ifstream myfile (argv[1], ios::in | ios::ate | ios::binary);
        streampos size;
        char * memblock;
        
        ifstream file (argv[1], ios::in|ios::binary|ios::ate);
        if (file.is_open())
        {
            size = file.tellg();
            memblock = new char [size];
            file.seekg (0, ios::beg);
            file.read (memblock, size);
            file.close();

			string x = "";
			for (int i = 0; i < size; ++i)
				x.push_back(memblock[i]);
			//cout << argv[1] <<endl;
			interpret(x);
        }
        
    }
	else
	{
		string file1;
		cin >> file1;
		streampos size;
        char * memblock;
        
        ifstream file (file1.data(), ios::in|ios::binary|ios::ate);
        if (file.is_open())
        {
            size = file.tellg();
            memblock = new char [size];
            file.seekg (0, ios::beg);
            file.read (memblock, size);
            file.close();

			string x = "";
			for (int i = 0; i < size; ++i)
				x.push_back(memblock[i]);
			//cout << argv[1] <<endl;
			interpret(x);
        }
	}
    system("PAUSE");
    return EXIT_SUCCESS;
}
