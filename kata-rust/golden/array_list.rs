use crate::types::List;

/// A growable array backed by a fixed-size boxed slice that we resize by hand.
pub struct ArrayList<T> {
    data: Box<[Option<T>]>,
    len: usize,
}

impl<T> ArrayList<T> {
    pub fn with_capacity(capacity: usize) -> Self {
        Self {
            data: Self::alloc(capacity),
            len: 0,
        }
    }

    fn alloc(capacity: usize) -> Box<[Option<T>]> {
        (0..capacity).map(|_| None).collect()
    }

    fn grow_if_full(&mut self) {
        if self.len < self.data.len() {
            return;
        }
        let mut data = Self::alloc((self.data.len() * 2).max(1));
        for (dst, src) in data.iter_mut().zip(self.data.iter_mut()) {
            *dst = src.take();
        }
        self.data = data;
    }
}

impl<T: Clone + PartialEq> List<T> for ArrayList<T> {
    fn len(&self) -> usize {
        self.len
    }

    fn prepend(&mut self, item: T) {
        self.insert_at(item, 0);
    }

    fn append(&mut self, item: T) {
        self.insert_at(item, self.len);
    }

    fn insert_at(&mut self, item: T, idx: usize) {
        assert!(
            idx <= self.len,
            "insert_at index {idx} out of bounds (len {})",
            self.len
        );
        self.grow_if_full();
        // Shift [idx, len) one to the right; the slot at `len` is None.
        self.data[idx..=self.len].rotate_right(1);
        self.data[idx] = Some(item);
        self.len += 1;
    }

    fn remove(&mut self, item: &T) -> Option<T> {
        let idx = self.data[..self.len]
            .iter()
            .position(|x| x.as_ref() == Some(item))?;
        self.remove_at(idx)
    }

    fn get(&self, idx: usize) -> Option<T> {
        if idx >= self.len {
            return None;
        }
        self.data[idx].clone()
    }

    fn remove_at(&mut self, idx: usize) -> Option<T> {
        if idx >= self.len {
            return None;
        }
        let item = self.data[idx].take();
        // Shift (idx, len) one to the left; the taken None ends up at len - 1.
        self.data[idx..self.len].rotate_left(1);
        self.len -= 1;
        item
    }
}
