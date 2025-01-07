#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct _tree;
typedef struct _tree* Position;
typedef struct _tree {
	int number;
	Position left;
	Position right;
}tree;

Position CreateNewElement(int number);
Position Insert(Position current, Position newElement);
int Inorder(Position current);
int Preorder(Position current);
int Postorder(Position current);
int Levelorder(Position current);
void PrintLevel(Position current, int level);
int Height(Position current);
Position FindElement(Position current, int element);
Position Delete(Position current, int element);
Position FindMin(Position current);

int main() {
	Position root = NULL;
	Position newElement = NULL;
	char odb = 0;
	int num = 0;
	printf("IZBORNIK:\n");
	printf("1- Unos novog elementa\n2- Inorder ispis\n3- Preorder ispis\n4- Postorder ispis\n5- Levelorder ispis\n6- Pronalazenje elementa\n7- Brisanje elementa\n8- Prekid programa\n");
	
	do {
		scanf("%c", &odb);
		switch (odb)
		{
		case '1':
			printf("\nUpisite broj koji zelite unijeti: ");
			scanf("%d", &num);
			newElement = CreateNewElement(num);
			if (!newElement)
				return -1;
			root = Insert(root, newElement);
			break;
		case '2':
			Inorder(root);
			printf("\n");
			break;
		case '3':
			Preorder(root);
			printf("\n");
			break;
		case '4':
			Postorder(root);
			printf("\n");
			break;
		case '5':
			Levelorder(root);
			printf("\n");
			break;
		case '6':
			printf("Upisite element koji zelite pronaci: ");
			scanf("%d", &num);
			if (FindElement(root, num))
				printf("Element %d postoji u stablu!\n", num);
			else
				printf("Element %d ne postoji u stablu!\n", num);
			break;
		case '7':
			printf("Upisite element koji zelite izbrisati: ");
			scanf("%d", &num);
			Delete(root, num);
			break;
		default:
			break;
		}
	} while (odb!='8');
	return 0;
}

Position CreateNewElement(int number) {
	Position newElement = NULL;
	newElement = (Position)malloc(sizeof(tree));
	if (!newElement) {
		printf("GRESKA PRI ALOKACIJI!");
		return NULL;
	}
	newElement->number = number;
	newElement->left = NULL;
	newElement->right = NULL;
	return newElement;
}

Position Insert(Position current, Position newElement) {
	if (current == NULL)
		return newElement;
	if (current->number < newElement->number)
		current->right = Insert(current->right, newElement);
	else if (current->number > newElement->number)
		current->left = Insert(current->left, newElement);
	else
		free(newElement);
	return current;
}

int Inorder(Position current) {
	if (current == NULL)
		return 0;
	Inorder(current->left);
	printf("%d ", current->number);
	Inorder(current->right);
	return 0;
}

int Preorder(Position current) {
	if (current == NULL)
		return 0;
	printf("%d ", current->number);
	Preorder(current->left);
	Preorder(current->right);
	return 0;
}

int Postorder(Position current) {
	if (current == NULL)
		return 0;
	Postorder(current->left);
	Postorder(current->right);
	printf("%d ", current->number);
	return 0;
}

int Levelorder(Position current) {
	int height = Height(current);
	for (int level = 1; level <= height; level++) {
		PrintLevel(current, level);
		printf(" ");
	}
	return 0;
}

void PrintLevel(Position current, int level) {
	if (current == NULL)
		return;
	if (level == 1) {
		printf("%d ", current->number);
	}
	else if (level > 1) {
		PrintLevel(current->left, level - 1);
		PrintLevel(current->right, level - 1);
	}
}

int Height(Position current) {
	if (current == NULL)
		return 0;
	int leftHeight = Height(current->left);
	int rightHeight = Height(current->right);
	return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

Position FindElement(Position current, int element) {
	if (current == NULL)
		return NULL;
	else if (current->number > element)
		return FindElement(current->left, element);
	else if (current->number < element)
		return FindElement(current->right, element);
	else
		return current;

}

Position Delete(Position current, int element) {
	Position temp = NULL;
	if (current == NULL)
		printf("\Element ne postoji u stablu!\n");
	else if (current->number > element)
		current->left = Delete(current->left, element);
	else if (current->number < element)
		current->right = Delete(current->right, element);
	else if (current->left != NULL && current->right != NULL) {
		temp = FindMin(current->right);
		current->number = temp->number;
		current->right = Delete(current->right, current->number);
	}
	else {
		temp = current;
		if (current->left == NULL)
			current = current->right;
		else
			current = current-> left;
		free(temp);
	}
	return current;
}

Position FindMin(Position current) {

	if (current == NULL)
		return NULL;
	else if (current->left == NULL)
		return current;
	else
		return FindMin(current->left);
}