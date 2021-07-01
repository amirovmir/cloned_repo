#include <iostream>

struct Node {
  int val;
  Node* next;
};

// Инициализации элемента односвязного списка нулями

void init(Node* node) {
	node->val = 0;
	node->next = NULL;
}

// Отображения односвязного списка на экран
void show(Node* head) {
  Node *p = head;
	while (p != NULL)
	{
		cout << p->val << " ";
		p = p->next;
	}
	cout << endl;
}

// Добавления элемента в односвязный список
void pushNode(Node* head,Node* node) {  
  Node* t = head;
  while (t->next != NULL) 
		t = t->next;
  *head = node;
  t->val = node->val;
  *head->next = t;  
} 


// Написать функцию инициализации size элементов списка заданным значением val.
void initList(Node* head, int size, int val)  {
  node->field = val;
	node->next = NULL;
}

// Написать функцию копирования элементов массива source в новый массив dest
void copyMas(Node* source, Node* dest) {
  while (source->next != NULL || dest->next != NULL) {
		dest->val = source->val;
		source = source->next;
		dest = dest->next;
}
  

// Написать функцию сравнение списков source и dest. Если списки равны 0, если не равны -1
int compareMas(Node* source, Node* dest) {
  return 0;
}


// Написать функцию удаления со сдвигом влево n-го элемента списка.
void deleteList(Node* head,int n) {

}


// Написать функцию сдвига значений вправо на n-элементов с заполнением крайних элементов нулями
void rShiftList(Node* head,int n) {

}



// Написать функцию сдвига значений влево на n-элементов с заполнением крайних элементов нулями.
void lShiftList(Node* head,int n) {

}


//Написать функцию сдвига значений влево на n-элементов с переносом вытесненных элементов в конец
void lRoundShiftMas(Node* head,int n, int size) {

}


// Написать функцию вычисления среднего значения элементов списка.
int averageList(Node* head, int size) {
  return 0;
}

// Написать функцию вычисления средне квадратического отклонения элементов списка.
int skoFromList(Node* head, int size) {
  return 0;
}

//tests
bool testInitNode()
{
	Node* t = new Node;

	init(t);
	if (t->val != 0)
	{
		return -1;
	}
	return 0;
}

bool testPushNode()
{
	Node* t = new Node;

	init(t);
	pushNode(t, new Node{ 1 });
	pushNode(t, new Node{ 2 });
	if ((t->next->val != 2) or (head->val != 1))
	{
		return -1;
	}
	return 0;
}

bool testCopyMas()
{
  Node* source = new Node;
	Node* dest = new Node;  
	Node* source_node = source;
	Node* dest_node = dest;
  
	init(source);
	init(dest);
  for (int i = 1; i < 11; i++) {
	  pushNode(source, new Node);
	  source_node->val = i;
	  source_node = source_node->next;
  }
  for (int j = 1; j < 11; j++) {
	  pushNode(dest, new Node);
	  dest_node->val = 1;
	  dest_node = dest_node->next;
  }
  copyMas(source,dest);
  for (int k = 1; k < 11; k++) {
	  if (source->val != dest->val)
    { 
      return -1;
    }
	  source = source->next;
	  dest = dest->next;	
  }
  return 0;    
}
  
static void runTest(int (*testFunction)(),const std::string& testName)
{
  if(testFunction()==0)
    std::cout << "Test "<< testName << " - OK" << std::endl;
  else 
    std::cout << "Test "<< testName << " - FAIL" << std::endl;
}



int main() 
{
  runTest(testInitNode, "Init test");
	runTest(testPushNode, "Push test");
  runTest(testCopyMas, "testCopyMas");
}
