#ifndef C_STR_H
#define C_STR_H

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
	void (*deconstructor)(struct Str *);
	void (*clear)(struct Str *);
	bool (*insert)(struct Str *, char *, int);
	bool (*append)(struct Str *, char *);
	struct Node* (*find_end_node)(struct Str *);
	char (*str_index)(struct Str*, unsigned int);
};

struct Str * Str_constructor();
void deconstructor(struct Str *this);
void clear(struct Str *this);
bool insert(struct Str *this, char *, int);
bool append(struct Str *this, char *value);
struct Node* find_end_node(struct Str *this);
char str_index(struct Str* this, unsigned int index);


struct Str * Str_constructor()
{
	struct Str *this;
	this = (struc Str *)malloc(sizeof(struc Str));
	this->head = NULL;
	this->num_node = 0;
	this->deconstructor = &deconstructor;
	this->clear = &clear;
	this->insert = &insert;
	this->append = &append;
	this->find_end_node = &find_end_node;
	this->str_index = &str_index;
	return this;
}

void deconstructor(struct Str *this)
{
	(*this->clear)(this);
	free(this);
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

bool insert(struct Str *this, char *value, int i)
{
	struct Node *obj, *temp;

	if(i >= this->num_node || i < 0)
	{
		return false;
	}
	else
	{
		obj = (struct Node *)malloc(sizeof(struct Node));
		obj->value = *value;
		temp = this->head;
		for(int j = 0; j < i - 1; j++)
		{
			temp = temp->next;
		}
		obj->next = temp->next;
		temp->next = obj;
		(this->num_node)++;
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
	if(this->num_node != 0 )
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

#endif
