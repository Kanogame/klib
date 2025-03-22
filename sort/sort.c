void sort_bubble(int *arr, int size) {
    int flag, tmp;
    for (int i = 0; i < size - 1; i++) {
        flag = 0;
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j+1]) {
                tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp; 
                flag = 1;
            }
        }
        if (!flag) 
            break; 
    }
}

static int min(int* arr, int size) {
    int min = arr[0];
    int id;
    for (int i = 1; i < size; i++) {
        if (arr[i] < min) {
            min = arr[i];
            id = i;
        }
    }
    return id;
}

void sort_selection(int *arr, int size) {
    int minid, tmp;
    for (int i = 0; i < size; i++) {
        minid = min(arr + (sizeof(int) * i),  size - i) + i;
        if (minid == i) {
            continue;
        }
        
        tmp = arr[minid];
        arr[minid] = arr[i];
        arr[i] = tmp;
    }
}

void sort_insertion(int *arr, int size) {
    int k, j;
    for (int i = 1; i < size; i++) {
        k = arr[i];
        j = i;
        while (j > 0 && arr[j-1] > k) {
            arr[j] = arr[j-1];
            j--;
        }
        arr[j] = k;
    }
}

int sort_bubbleComp(void **arr, int size, int (*bigger)(void*, void*)) {
    int flag, rep =0;
    void * tmp;
    for (int i = 0; i < size - 1; i++) {
        flag = 0;
        for (int j = 0; j < size - i - 1; j++) {
            if (bigger(arr[j], arr[j+1])) {
                flag = 1;
                rep++;
                tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp; 
            }
        }
    }
    return rep;
}

static int minComp(void** arr, int size, int (*bigger)(void*, void*)) {
    void *min = arr[0];
    int id;
    for (int i = 1; i < size; i++) {
        if (!bigger(arr[i], min)) {
            min = arr[i];
            id = i;
        }
    }
    return id;
}

void sort_selectionComp(void **arr, int size, int (*bigger)(void*, void*)) {
    int minid;
    void* tmp;
    for (int i = 0; i < size; i++) {
        minid = minComp(arr + (sizeof(void *) * i),  size - i, bigger) + i;
        if (minid == i) {
            continue;
        }
        
        tmp = arr[minid];
        arr[minid] = arr[i];
        arr[i] = tmp;
    }
}

void sort_insertionComp(void **arr, int size, int (*bigger)(void*, void*)) {
    void* k;
    int j;
    for (int i = 1; i < size; i++) {
        k = arr[i];
        j = i;
        while (j > 0 && bigger(arr[j-1], k)) {
            arr[j] = arr[j-1];
            j--;
        }
        arr[j] = k;
    }
}