/*
-----------------------------------------------------***Заголовок: Max, Min elements
*/


// #include <iostream>

// int main() {

//     int array[] = {1000, 1001, 999, 2000};
//     size_t sizeArr = sizeof(array) / sizeof(array[0]);

//     int MaxElement = array[0];
//     int MinElement = array[0];
//     for (size_t i = 0; i < sizeArr; i++) {
//         if (array[i] > MaxElement) {
//             MaxElement = array[i];
//         }
//         if (array[i] < MinElement) {
//             MinElement = array[i];
//         }
//     }

//     std::cout << "Max Element: " << MaxElement << ", Min ElementL: " 
//                                  << MinElement << std::endl;

//     return 0;
// }


/*
-----------------------------------------------------***Заголовок: Bubble sort
*/


// #include <iostream>

// void bubbleSort(int arr[], size_t sizeArr);
// void printArray(int arr[], size_t sizeArr);

// int main() {

//     int array[] = {1, 4, 3, 2, 6, 5, 9, 8, 7, 10};
//     size_t sizeArray = sizeof(array) / sizeof(array[0]);

//     printArray(array, sizeArray);

//     bubbleSort(array, sizeArray);

//     printArray(array, sizeArray);

//     return 0;;
// }

// void bubbleSort(int arr[], size_t sizeArr) {
//     for (size_t i = 0; i < sizeArr - 1; i++) {
//         for (size_t j = 0; i < sizeArr - j; j++) {
//             if (arr[j] > arr[j + 1]) { // Чтобы поменять порядок сортировки меняем ">" на "<"
//                 int temp = arr[j + 1];
//                 arr[j + 1] = arr[j];
//                 arr[j] = temp;
//             }
//         }
//     }
// }

// void printArray(int arr[], size_t sizeArr) {
//     for (size_t i = 0; i < sizeArr; i++)
//         std::cout << arr[i] << (i < sizeArr - 1 ? ", " : ".\n");
// }


/*
Quick sort
*/


// #include <iostream>

// void swap (int* a, int* b);
// int partition(int arr[], int low, int high);
// void quickSort(int arr[], int low, int high);
// void printArray(int arr[], size_t sizeArr);

// int main() {

//     int array[] = {1, 4, 3, 2, 6, 5, 9, 8, 7, 10};
//     size_t sizeArray = sizeof(array) / sizeof(array[0]);
//     int low = 0;
//     int high = sizeArray - 1;

//     printArray(array, sizeArray);

//     quickSort(array, low, high);

//     printArray(array, sizeArray);

//     return 0;;
// }

// void swap (int* a, int* b) {
//     int temp = *b;
//     *b = *a;
//     *a = temp;
// }

// int partition(int arr[], int low, int high) {
//     int pivot = arr[high];
//     int i = low - 1;
//     for (int j = low; j < high; j++) {
//         if (arr[j] <= pivot) {
//             i++;
//             swap(&arr[i], &arr[j]);
//         }
//     }
//     swap(&arr[i + 1], &arr[high]);
//     return i + 1;
// }

// void quickSort(int arr[], int low, int high) {
//     if (low < high) {
//         int pi = partition(arr, low, high);
//         quickSort(arr, low, pi - 1);
//         quickSort(arr, pi + 1, high);
//     }
// }

// void printArray(int arr[], size_t sizeArr) {
//     for (size_t i = 0; i < sizeArr; i++)
//         std::cout << arr[i] << (i < sizeArr - 1 ? ", " : ".\n");
// }


/*
-----------------------------------------------------***Заголовок: Linear search
*/


// #include <iostream>

// int linearSearch(int arr[], size_t sizeArr, int value);

// int main() {

// int array[] {1, 3, 10, 22, 15, 2, 5, 46, 12};
// size_t sizeArr = sizeof(array) / sizeof(array[0]);

// int desValue = 10;
// int position = linearSearch(array, sizeArr, desValue);

// if (position != -1) {
//     std::cout << "The Index of the desired value: " 
//               << position << std::endl;
// } else {
//     std::cout << "The value was not found in the array" << std::endl;
// }

//     return 0;
// }

// int linearSearch(int arr[], size_t sizeArr, int value) {
//     for (size_t i = 0; i < sizeArr; i++) {
//         if (arr[i] == value) {
//             return i;
//         }
//     }
//     return -1;
// }


/*
Binary search
*/


#include <iostream>

int main() {

    std::cout << 15 / 2 << std::endl;

    return 0;
}


/*
-----------------------------------------------------***Заголовок: Алгоритм односвязного списка
*/

// #include <iostream>

// struct node {
//     int data;
//     node* next;
// };

// void append(node** headRef, int newData);
// void printNode(node* head);
// void freeMemory(node* head);

// int main() {

//     node* head = nullptr;

//     append(&head, 10);
//     append(&head, 20);
//     append(&head, 30);

//     printNode(head);

//     freeMemory(head);

//     return 0;
// }

// void append(node** headRef, int newData) {
//     node* newNode = new node();

//     newNode->data = newData;
//     newNode->next = nullptr;

//     if (*headRef == nullptr) {
//         *headRef = newNode;
//         return;
//     }

//     node* last = *headRef;
//     while (last->next != nullptr) {
//         last = last->next;
//     }

//     last->next = newNode;
// }

// void printNode(node* head) {
//     while (head != nullptr) {
//         std::cout << head->data << " -> ";
//         head = head->next;
//     }
//     std::cout << "nullptr" << std::endl;
// }

// void freeMemory(node* head) {
//     while (head != nullptr) {
//         node* temp = head;
//         head = head->next;
//         delete[] temp;
//     }
// }

