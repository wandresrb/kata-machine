use kata::code::trie::Trie;

fn sorted(mut words: Vec<String>) -> Vec<String> {
    words.sort();
    words
}

#[test]
fn trie() {
    let mut trie = Trie::new();
    trie.insert("foo");
    trie.insert("fool");
    trie.insert("foolish");
    trie.insert("bar");

    assert_eq!(sorted(trie.find("fo")), ["foo", "fool", "foolish"]);

    trie.delete("fool");

    assert_eq!(sorted(trie.find("fo")), ["foo", "foolish"]);
}
