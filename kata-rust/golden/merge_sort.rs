pub fn merge_sort(arr: &mut [i32]) {
    if arr.len() <= 1 {
        return;
    }
    let mid = arr.len() / 2;
    merge_sort(&mut arr[..mid]);
    merge_sort(&mut arr[mid..]);

    let (left, right) = (arr[..mid].to_vec(), arr[mid..].to_vec());
    let (mut i, mut j) = (0, 0);
    for slot in arr.iter_mut() {
        if j >= right.len() || (i < left.len() && left[i] <= right[j]) {
            *slot = left[i];
            i += 1;
        } else {
            *slot = right[j];
            j += 1;
        }
    }
}
