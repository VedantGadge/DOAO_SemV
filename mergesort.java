import java.util.Scanner;

public class mergesort {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int[] arr = new int[n];
        
        for (int i = 0 ;i<n;i++) {
            int num = sc.nextInt();
            arr[i] = num;
        }
        divide(arr,0,n-1);
        for (int i = 0 ;i<n;i++) {
            System.out.println(arr[i]);
        }
    }

    static void merge(int[] arr, int low, int mid, int high) {
        int merged[] = new int[high - low + 1];
        int left = low;
        int right = mid + 1;
        int x = 0;
        while (left <= mid && right <= high) {
            if (arr[left] <= arr[right]) {
                merged[x++] = arr[left++];
            }
            else{
                merged[x++] = arr[right++];
            }
        }
        while (left<=mid) {
            merged[x++] = arr[left++];
        }
        while (right<=high) {
            merged[x++] = arr[right++];
        }
        for (int i = 0, j = low; i < merged.length; i++, j++) {
            arr[j] = merged[i];
        }
    }
    static void divide(int[] arr , int low , int high){
        if (low >= high) return;
            int mid = low + (high-low)/2;
            divide(arr, low, mid);
            divide(arr, mid+1, high);
            merge(arr,low, mid , high);
    }
}
