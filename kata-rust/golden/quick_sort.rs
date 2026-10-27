pub fn quick_sort(arr: &mut [i32]) {
    if arr.len() <= 1 {
        return;
    }
    let pivot = partition(arr);
    let (left, right) = arr.split_at_mut(pivot);
    quick_sort(left);
    quick_sort(&mut right[1..]);
}

/// Lomuto partition around the last element; returns the pivot's final index.
fn partition(arr: &mut [i32]) -> usize {
    let hi = arr.len() - 1;
    let pivot = arr[hi];
    let mut idx = 0;
    for i in 0..hi {
        if arr[i] <= pivot {
            arr.swap(i, idx);
            idx += 1;
        }
    }
    arr.swap(idx, hi);
    idx
}
