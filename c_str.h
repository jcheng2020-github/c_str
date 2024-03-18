#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

struct Node{
	char value;
	struct Node* next;
};

struct Str{
	struct Node* head;
	unsigned int num_node;
	void (*constructor)(struct Str *);
	void (*deconstructor)(struct Str *);
	void (*clear)(struct Str *);
	bool (*append)(struct Str *, char *);
	struct Node* (*find_end_node)(struct Str *);
	char (*str_index)(struct Str*, unsigned int);
};

void constructor(struct Str *this);
void deconstructor(struct Str *this);
void clear(struct Str *this);
bool append(struct Str *this, char *value);
struct Node* find_end_node(struct Str *this);
char str_index(struct Str* this, unsigned int index);


void constructor(struct Str *this)
{
	this->head = NULL;
	this->num_node = 0;
}

void deconstructor(struct Str *this)
{
	(*this->clear)(this);
}

void clear(struct Str *this)
{
	struct Node *node1,*node2;
	if(this->num_node != 0)
	{
		node1 = this->head;
		node2 = node1->next;
		free(node1);
		(this->num_node)--;
		while(node2 != NULL)
		{
			node1 = node2;
			node2 = node2->next;
			free(node1);
			(this->num_node)--;
		}
	}
}

bool append(struct Str *this, char *value)
{
	struct Node* end_node;

	if(this->num_node == 0)
	{
		this->head = (struct Node*)malloc(sizeof(struct Node));	
		this->head->value = *value;
		this->head->next = NULL;
		(this->num_node)++;
		return true;
	}
	if(this->num_node != 0 && this->num_node < (pow(2,sizeof(unsigned int)*8) - 1))
	{
		end_node = (*this->find_end_node)(this);
		end_node->next = (struct Node*)malloc(sizeof(struct Node));
		end_node->next->value = *value;
		end_node->next->next = NULL;
		(this->num_node)++;
		return true;
	}
	return false;
}

struct Node* find_end_node(struct Str *this)
{
	struct Node* result;
	if(this->num_node == 0)
	{
		return NULL;
	}
	if(this->num_node == 1)
	{
		return this->head;
	}
	if(this->num_node != 1 && this->num_node != 0 && this->num_node <= (pow(2,sizeof(unsigned int)*8)-1))
	{
		result = this->head;
		while(result->next != NULL)
		{
			result = result->next;
		}
		return result;
	}
	else
	{
		printf("Warning: the num_node of struct Str is abnormal\n");
		return NULL;
	}
}

char str_index(struct Str* this, unsigned int index)
{
	char result;
	struct Node *slid;

	if(index >= 0 && index <= (this->num_node - 1))
	{
		int i = 0;
		slid = this->head;
		while(i != index)
		{
			i++;
			slid = slid->next;
		}
		return slid->value;
	}
	if(index > (this->num_node - 1))
	{
		printf("Warning: index is out of range determined by num_node of struct Str\n");
		return '\0';
	}
	else
	{
		printf("Warning: index is out of range, smaller than 0\n");
		return '\0';
	}
}