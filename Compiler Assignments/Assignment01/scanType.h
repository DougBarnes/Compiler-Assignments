#ifndef SCANTYPE_H
#define SCANTYPE_H
struct TokenData {
	int stringLength;		// length of a string
    int  tokenclass;        // token class
    int  linenum;           // line where found
    char *tokenstr;         // what string was actually read
    char cvalue;            // any character value
    int idIndex;            // index for id
    int  numValue;          // any numeric value or Boolean value
    int countValue;	    	// any counting of length
    char *svalue;           // any string value e.g. an id
    char avalue[];	    	// any array 
};

#endif
