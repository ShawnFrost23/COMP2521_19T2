// data structures representing CharList
struct CharListNode {
	char *data;           /**< value of this list item */
	struct CharListNode *next;
	                    /**< pointer to node containing next element */
};

struct CharListRep {
	struct CharListNode *first;
	                    /**< node containing first value */
	struct CharListNode *last;
	                    /**< node containing last value */
};
typedef struct CharListRep *CharList;

//Create a new, empty IntList.
CharList newCharList (void);

//  create a new IntListNode with value v
struct CharListNode *newCharListNode (char *str);

//Insert in a our list.
void CharListInsert (CharList L, char *str);
