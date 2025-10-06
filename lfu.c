#include <stdio.h>

int main() {
    int n, f;
    printf("Enter number of pages: ");
    scanf("%d", &n);

    int pages[n];
    printf("Enter page reference string: ");
    for(int i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &f);

    int frames[f], freq[f], faults = 0;
    for(int i = 0; i < f; i++) {
        frames[i] = -1;  // empty frame
        freq[i] = 0;     // frequency count
    }

    printf("\nPage\tFrames\n-------------------\n");

    for(int i = 0; i < n; i++) {
        int page = pages[i], found = -1;

        // check if page is already in frames
        for(int j = 0; j < f; j++) {
            if(frames[j] == page) {
                found = j;
                freq[j]++;  // increment frequency
                break;
            }
        }

        if(found == -1) { // page fault
            faults++;
            int replace = -1;

            // find empty frame
            for(int j = 0; j < f; j++) {
                if(frames[j] == -1) {
                    replace = j;
                    break;
                }
            }

            // if no empty frame, replace LFU page
            if(replace == -1) {
                int minFreq = freq[0];
                replace = 0;
                for(int j = 1; j < f; j++) {
                    if(freq[j] < minFreq) {
                        minFreq = freq[j];
                        replace = j;
                    }
                }
            }

            frames[replace] = page;
            freq[replace] = 1;
        }

        // print frames after each step
        printf("%d\t", page);
        for(int j = 0; j < f; j++)
            if(frames[j] != -1) printf("%d(%d) ", frames[j], freq[j]);
            else printf("- ");
        printf("\n");
    }

    printf("-------------------\nTotal Page Faults = %d\n", faults);
    return 0;
}
