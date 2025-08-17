import java.util.Scanner;

public class quicksort {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int[] arr = new int[n];
        
        for (int i = 0 ;i<n;i++) {
            int num = sc.nextInt();
            arr[i] = num;
        }
        quick_sort(arr, 0, n - 1);
        for (int v : arr) {
            System.out.print(v + " ");
        }
        sc.close();
    }

    static void quick_sort(int[] arr, int low , int high){
        if(low < high){
            int pivotIndex = partition(arr , low , high);
            quick_sort(arr, low, pivotIndex - 1);
            quick_sort(arr, pivotIndex + 1, high);
        }
    }

    static int partition(int[] arr , int low , int high){
        int pivot = arr[low];
        int left = low + 1;
        int right = high;
        while (true) {
            while (left <= right && arr[left] < pivot) left++;
            while (left <= right && arr[right] > pivot) right--;
            if (left >= right) break;
            swap(arr, left, right);
            left++;
            right--;
        }
        swap(arr, low, right); // place pivot in correct position
        return right;
    }

    static void swap(int[] arr, int i, int j){
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}
