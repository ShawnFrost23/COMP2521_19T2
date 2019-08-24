
// creates a new empty tfidf list.
TfIdfList newTfIdfList (void);

//creats a new tfidf node with a given file name, tfidf value.
struct TfIdfNode *newTfidfNode(char *filename, double tfidfVal);

//Inserts in the tfidf list in order of the tfidf_sum value.
TfIdfList TfidfInsertInOrder(TfIdfList L, char *filename, double tfidfVal);

//Finds and returns the node with given filename.
TfIdfList TfidfListFind(TfIdfList L, char *filename);

//Inserts a node with given filename and tfidf value.
//If the node with given filename already exists then it adds the tfidf value to the tfidf_sum.
TfIdfList TfidfListInsert(TfIdfList L, char *filename, double tfidfVal);

//checks weather a given filename is in the given FileList or not.
int fileNameInList(TfIdfList L, char *filename);
