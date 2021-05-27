#include "readfile.h"


/**
 * Function that parses a line and returns all the space separated numbers as vectors
 * @param line character array line to be parsed
 * @param len length of the line to be parsed
 * @return integer vector storing all the numbers in the line.
*/
vector <int> parse_line(char *line,int len)
{
    
    vector<int> args;

    int i=0;
    int sum=0;
    bool start = false;

    while(i<len)    //loop till the line is not finished
    {
        if(line[i]>='0' && line[i]<='9')    // check if the character is a digit 
        {
            if(!start) start = true;        // if yes change the current number 
            sum *= 10;
            sum += line[i]-'0';
        }

        if(!(line[i]>='0' && line[i]<='9') && start) //if character is not a number then ignore 
        {
            args.push_back(sum);
            start = false;
            sum = 0;
        }
        if(line[i]=='\n')break;
        i++;
    }
    return args;
}

/**
 * Function that parses a file line by line and initializes a graph object
 * @param filename stores the filename to be openend
 * @return Graph object containing all the data regarding the graph
*/
Graph* parse_file(char * filename)
{
    FILE * fptr = fopen(filename,"r");          //opening the file in read mode 
    if(fptr==NULL)
    {
        printf("File %s not found. Exiting... \n",filename);
        return NULL;                            // returns a NULL pointer if file does not exists 
    }

    int line_count = 0;                         // Keeping track of line count
    
    char line[64];                              // Buffer to store the line

    if(fgets(line,64,fptr)==NULL)               
    {
        printf("File is empty. Exiting ...\n");
        return NULL;   
    }

    line_count++;

    vector<int> argV = parse_line(line,64);     // Parsing the line to extract source destination and allowed pot limit

    if(argV.size() < 3)
    {
        printf("Missing values in first line. Exiting ...\n");
        return NULL;
    }

    Graph * G = new Graph(argV[0],argV[1],argV[2]); //Initializing graph object

    while(fgets(line,64,fptr)!=NULL)        
    {
        argV = parse_line(line,64);             //Parsing multiple lines
        line_count++;
        if(argV.size() < 4)
        {
            printf("Missing values at line %d .Exiting...\n",line_count);
            return NULL;
            break;
        }
        G->addEdge(argV[0],argV[1],argV[2],argV[3]);    //Updating the edges of graph
    }
    
    return G;
}
