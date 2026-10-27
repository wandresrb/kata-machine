/// Binary min-heap stored in a `Vec`: children of `i` are `2i + 1` and `2i + 2`.
#[derive(Default)]
pub struct MinHeap {
    data: Vec<i32>,
}

impl MinHeap {
    pub fn new() -> Self {
        Self::default()
    }

    pub fn insert(&mut self, value: i32) {
        self.data.push(value);
        self.heapify_up(self.data.len() - 1);
    }

    pub fn delete(&mut self) -> Option<i32> {
        if self.data.is_empty() {
            return None;
        }
        let out = self.data.swap_remove(0);
        self.heapify_down(0);
        Some(out)
    }

    pub fn len(&self) -> usize {
        self.data.len()
    }

    pub fn is_empty(&self) -> bool {
        self.len() == 0
    }

    fn heapify_up(&mut self, mut idx: usize) {
        while idx > 0 {
            let parent = (idx - 1) / 2;
            if self.data[parent] <= self.data[idx] {
                break;
            }
            self.data.swap(parent, idx);
            idx = parent;
        }
    }

    fn heapify_down(&mut self, mut idx: usize) {
        loop {
            let (l, r) = (2 * idx + 1, 2 * idx + 2);
            let mut smallest = idx;
            if l < self.data.len() && self.data[l] < self.data[smallest] {
                smallest = l;
            }
            if r < self.data.len() && self.data[r] < self.data[smallest] {
                smallest = r;
            }
            if smallest == idx {
                return;
            }
            self.data.swap(idx, smallest);
            idx = smallest;
        }
    }
}
