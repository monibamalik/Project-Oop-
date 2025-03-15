#include <iostream>
using namespace std;
class SortingAlgorithms {
public:
    static void bubbleSort(int arr[], int size, bool ascending);
    static void insertionSort(int arr[], int size, bool ascending);
    static void selectionSort(int arr[], int size, bool ascending);

    static void mergeSort(int arr[], int left, int right, bool ascending);
    static void merge(int arr[], int left, int mid, int right, bool ascending);

    static void quickSort(int arr[], int low, int high, bool ascending);
    static int partition(int arr[], int low, int high, bool ascending);

    static void radixSort(int arr[], int size, bool ascending);
    static void bucketSort(int arr[], int size, bool ascending);
    static void countSort(int arr[], int size, bool ascending);
};

void SortingAlgorithms::bubbleSort(int arr[], int size, bool ascending) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            // Swap elements if they are in the wrong order
            if ((ascending && arr[j] > arr[j + 1]) || (!ascending && arr[j] < arr[j + 1])) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void SortingAlgorithms::insertionSort(int arr[], int size, bool ascending) {
    for (int i = 1; i < size; ++i) {
        int key = arr[i];
        int j = i - 1;

        // Move elements greater than key to one position ahead of their current position
        while ((ascending && j >= 0 && arr[j] > key) || (!ascending && j >= 0 && arr[j] < key)) {
            arr[j + 1] = arr[j];
            --j;
        }

        arr[j + 1] = key;
    }
}

void SortingAlgorithms::selectionSort(int arr[], int size, bool ascending) {
    for (int i = 0; i < size - 1; ++i) {
        int minIndex = i;

        for (int j = i + 1; j < size; ++j) {
            // Find the index of the minimum (or maximum) element
            if ((ascending && arr[j] < arr[minIndex]) || (!ascending && arr[j] > arr[minIndex])) {
                minIndex = j;
            }
        }

        // Swap the found minimum (or maximum) element with the first element
        swap(arr[i], arr[minIndex]);
    }
}

void SortingAlgorithms::mergeSort(int arr[], int left, int right, bool ascending)
{
    if (left < right) 
	{
		//This line calculates the middle index of the current subarray
        int mid = left + (right - left) / 2;//to avoid overflow issues is not calculate directly (left + right) / 2
        mergeSort(arr, left, mid, ascending);// Sort first halves
        mergeSort(arr, mid + 1, right, ascending);// Sort second halves
        // Merge the sorted halves
        merge(arr, left, mid, right, ascending);//After sorting the left and right halves this line calls the merge function
    }
}

void SortingAlgorithms::merge(int arr[], int left, int mid, int right, bool ascending)
{
    int n1 = mid - left + 1;//calculate size of left array n1
    int n2 = right - mid;//calculate size of right array n2

    // Create temporary arrays
    int* leftArr = new int[n1];
    int* rightArr = new int[n2];

    // Copy data to temporary arrays L[] and R[]
    for (int i = 0; i < n1; ++i)
    {
        leftArr[i] = arr[left + i];//the process of copying the elements from the original array to the temporary left array
    }
    for (int j = 0; j < n2; ++j)
    {
        rightArr[j] = arr[mid + 1 + j];//the process of copying the elements from the original array to the temporary right array
    }
    // Merge the temporary arrays back into arr[left..right]
    int i = 0;// Initial index of first subarray
	int j = 0;// Initial index of second subarray
	int k = left;// Initial index of merged subarray
    while (i < n1 && j < n2)// merging process within elements remaining in both the left and right halves to be merged
	{
		//pahli condition ascending k lia hi or dosri descending k lia
        if ((ascending && leftArr[i] <= rightArr[j]) || (!ascending && leftArr[i] >= rightArr[j]))
		{
            arr[k] = leftArr[i];
            ++i;
        }
		else
		{
            arr[k] = rightArr[j];//right subarray ka element smaller hi left say to ya right waly ko store kar dy sorted array main
            ++j;
        }
        ++k;
    }
    // Copy the remaining elements of L[]
    while (i < n1)
	{
        arr[k] = leftArr[i];
        ++i;
        ++k;
    }
    // Copy the remaining elements of R[]
    while (j < n2) 
	{
        arr[k] = rightArr[j];
        ++j;
        ++k;
    }

    delete[] leftArr;
    delete[] rightArr;
}

void SortingAlgorithms::quickSort(int arr[], int low, int high, bool ascending) {
    if (low < high) {
        // Partition the array and get the pivot index
        int pivotIndex = partition(arr, low, high, ascending);

        // Recursively sort the subarrays
        quickSort(arr, low, pivotIndex - 1, ascending);
        quickSort(arr, pivotIndex + 1, high, ascending);
    }
}

int SortingAlgorithms::partition(int arr[], int low, int high, bool ascending) {
    // Choose the rightmost element as the pivot
    int pivot = arr[high];

    // Find the index where the pivot belongs in the sorted array
    int i = low - 1;
    for (int j = low; j <= high - 1; ++j) {
        if ((ascending && arr[j] <= pivot) || (!ascending && arr[j] >= pivot)) {
            ++i;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void SortingAlgorithms::radixSort(int arr[], int size, bool ascending) 
{
    int maxNumber = arr[0];
    // Find the maximum element in the array
    for (int i = 1; i < size; ++i)//Iterates through the array starting from the second element
	{
        if (arr[i] > maxNumber)//if the current element arr[i] is greater than the current maximum element maxNumber
		{
            maxNumber = arr[i];//If the current element is greater than the current maximum, updates maxNumber to the value of the current element
        }
    }
    // Iterate through each digit place (1s, 10s, 100s, etc.)
    for (int exp = 1; maxNumber / exp > 0; exp *= 10)
	{
        countSort(arr, size, ascending); // Use counting sort for each digit place
    }
}

void SortingAlgorithms::bucketSort(int arr[], int size, bool ascending) 
{
    int maxNumber = arr[0];
    for (int i = 1; i < size; ++i)
	{
        if (arr[i] > maxNumber)
		{
            maxNumber = arr[i];
        }
    }

    const int BUCKET_SIZE = 10;
    int buckets[BUCKET_SIZE][size + 1];

    for (int i = 0; i < BUCKET_SIZE; ++i)
	{
        buckets[i][0] = 0;
    }

    for (int i = 0; i < size; ++i)
	{
        int bucketIndex;
        if (ascending)
		{
            bucketIndex = BUCKET_SIZE * arr[i] / (maxNumber + 1);
        }
		else
		{
            // For descending order, calculate the bucket index based on the complement of the value
            bucketIndex = BUCKET_SIZE - 1 - BUCKET_SIZE * arr[i] / (maxNumber + 1);
        }
        buckets[bucketIndex][++buckets[bucketIndex][0]] = arr[i];
    }

    int index = 0;
    for (int i = 0; i < BUCKET_SIZE; ++i)
	{
        SortingAlgorithms::insertionSort(buckets[i] + 1, buckets[i][0], ascending);
        for (int j = 1; j <= buckets[i][0]; ++j)
		{
            arr[index++] = buckets[i][j];
        }
    }
}

void SortingAlgorithms::countSort(int arr[], int size, bool ascending) 
{
	// Find the maximum and minimum elements in the array
    int maxElement = arr[0];
    int minElement = arr[0];
    //Yeh loop array ke elements par chalta hai 
    for (int i = 1; i < size; ++i)//lekin yeh 1 se shuru hota hi kiu ke pehla element pehle iteration mein hi maximum aur minimum ke liye consider ho chuka hi
	{
        if (arr[i] > maxElement)//Is se array ka sab se bada element pata chalta hi
		{
            maxElement = arr[i];//Agar shart true hoti hi to current element ko naya maximum banaya jata hai
        }
        if (arr[i] < minElement)//Is se yeh maloom hota hai ke array mein konsa sab se chhota element hai
		{
            minElement = arr[i];// Agar shart true hoti hi to current element ko naya minimum banaya jata hai
        }
    }

    int range = maxElement - minElement + 1;//range find karny k lia

    // Create count array to store the count of each element
    int count[range] = {0};

    // Update the count array with the frequency of each element
    for (int i = 0; i < size; ++i) 
	{
        count[arr[i] - minElement]++;//Har element ko apni frequency k mutabiq index par main increment kiya jata hai
		//Is say pata chalta hi k har element ki frequency kia hai
    }

    // Update the count array to store the count
    for (int i = 1; i < range; ++i) //Yeh count array mein har element ki frequency ko uske previous element ke frequency ke sath jodta hai
	{
        count[i] += count[i - 1];//Har iteration mein current element ki frequency ko uske previous element k frequency k sath jodta hi
    }

    // Create a temporary array to store the sorted result
    int output[size];

    // Build the output array
    for (int i = size - 1; i >= 0; --i)
	{
        output[count[arr[i] - minElement] - 1] = arr[i];
        count[arr[i] - minElement]--;
    }

    // Copy the output array to the original array
    for (int i = 0; i < size; ++i)
	{
        arr[i] = output[i];
    }

    // Reverse the array if sorting in descending order
    if (!ascending)
	{
        for (int i = 0; i < size / 2; ++i)
		{
            swap(arr[i], arr[size - i - 1]);
        }
    }
}

void printArray(const int arr[], int size) {
    for (int i = 0; i < size; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    const int MAX_SIZE = 1000;
    int arr[MAX_SIZE];
    int size;

    cout << "Enter the size of the array: ";
    cin >> size;

    cout << "Enter the elements of the array:\n";
    for (int i = 0; i < size; ++i) {
        cout << "Element " << i + 1 << ": ";
        cin >> arr[i];
    }

    int choice;
    cout << "Choose a sorting algorithm:\n"
              << "1. Bubble Sort\n"
              << "2. Insertion Sort\n"
              << "3. Selection Sort\n"
              << "4. Merge Sort\n"
              << "5. Quick Sort\n"
              << "6. Radix Sort\n"
              << "7. Bucket Sort\n"
              << "8. Count Sort\n";
    cout << "Enter your choice (1-8): ";
    cin >> choice;

    bool ascending;
    cout << "Sort in ascending (1) or descending (0) order: ";
    cin >> ascending;

    switch (choice) {
    case 1:
        SortingAlgorithms::bubbleSort(arr, size, ascending);
        break;
    case 2:
        SortingAlgorithms::insertionSort(arr, size, ascending);
        break;
    case 3:
        SortingAlgorithms::selectionSort(arr, size, ascending);
        break;
    case 4:
        SortingAlgorithms::mergeSort(arr, 0, size - 1, ascending);
        break;
    case 5:
        SortingAlgorithms::quickSort(arr, 0, size - 1, ascending);
        break;
    case 6:
        SortingAlgorithms::radixSort(arr, size, ascending);
        break;
    case 7:
        SortingAlgorithms::bucketSort(arr, size, ascending);
        break;
    case 8:
        SortingAlgorithms::countSort(arr, size, ascending);
        break;
    default:
        cout << "Invalid choice\n";
        return 1;
    }

    cout << "Sorted array using the chosen algorithm:\n";
    printArray(arr, size);

    return 0;
}
