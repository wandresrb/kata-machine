use std::hash::{DefaultHasher, Hash, Hasher};

const INITIAL_BUCKETS: usize = 8;
const MAX_LOAD: f64 = 0.75;

/// Separate-chaining hash map.
pub struct Map<K, V> {
    buckets: Vec<Vec<(K, V)>>,
    len: usize,
}

impl<K: Hash + Eq, V> Default for Map<K, V> {
    fn default() -> Self {
        Self {
            buckets: Self::empty_buckets(INITIAL_BUCKETS),
            len: 0,
        }
    }
}

impl<K: Hash + Eq, V: Clone> Map<K, V> {
    pub fn new() -> Self {
        Self::default()
    }

    pub fn get(&self, key: &K) -> Option<V> {
        self.buckets[self.bucket_of(key)]
            .iter()
            .find(|(k, _)| k == key)
            .map(|(_, v)| v.clone())
    }

    pub fn set(&mut self, key: K, value: V) {
        let b = self.bucket_of(&key);
        if let Some(entry) = self.buckets[b].iter_mut().find(|(k, _)| *k == key) {
            entry.1 = value;
            return;
        }
        self.buckets[b].push((key, value));
        self.len += 1;
        if self.len as f64 / self.buckets.len() as f64 > MAX_LOAD {
            self.rehash(self.buckets.len() * 2);
        }
    }

    pub fn delete(&mut self, key: &K) -> Option<V> {
        let b = self.bucket_of(key);
        let pos = self.buckets[b].iter().position(|(k, _)| k == key)?;
        self.len -= 1;
        Some(self.buckets[b].swap_remove(pos).1)
    }

    pub fn size(&self) -> usize {
        self.len
    }
}

impl<K: Hash + Eq, V> Map<K, V> {
    fn empty_buckets(n: usize) -> Vec<Vec<(K, V)>> {
        (0..n).map(|_| Vec::new()).collect()
    }

    fn bucket_of(&self, key: &K) -> usize {
        let mut hasher = DefaultHasher::new();
        key.hash(&mut hasher);
        (hasher.finish() % self.buckets.len() as u64) as usize
    }

    fn rehash(&mut self, n: usize) {
        let old = std::mem::replace(&mut self.buckets, Self::empty_buckets(n));
        for (k, v) in old.into_iter().flatten() {
            let b = self.bucket_of(&k);
            self.buckets[b].push((k, v));
        }
    }
}
