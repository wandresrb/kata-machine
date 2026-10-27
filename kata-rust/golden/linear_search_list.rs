pub fn linear_search(haystack: &[i32], needle: i32) -> bool {
    for &x in haystack {
        if x == needle {
            return true;
        }
    }
    false
}
