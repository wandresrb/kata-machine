/// Growable ring buffer: `push` appends at the tail, `pop` removes the oldest item.
pub struct RingBuffer<T> {
    buf: Vec<Option<T>>,
    head: usize,
    len: usize,
}

impl<T> Default for RingBuffer<T> {
    fn default() -> Self {
        Self {
            buf: Vec::new(),
            head: 0,
            len: 0,
        }
    }
}

impl<T: Clone> RingBuffer<T> {
    pub fn new() -> Self {
        Self::default()
    }

    pub fn push(&mut self, item: T) {
        if self.len == self.buf.len() {
            self.grow();
        }
        let tail = (self.head + self.len) % self.buf.len();
        self.buf[tail] = Some(item);
        self.len += 1;
    }

    pub fn pop(&mut self) -> Option<T> {
        if self.len == 0 {
            return None;
        }
        let item = self.buf[self.head].take();
        self.head = (self.head + 1) % self.buf.len();
        self.len -= 1;
        item
    }

    pub fn get(&self, idx: usize) -> Option<T> {
        if idx >= self.len {
            return None;
        }
        self.buf[(self.head + idx) % self.buf.len()].clone()
    }

    pub fn len(&self) -> usize {
        self.len
    }

    pub fn is_empty(&self) -> bool {
        self.len() == 0
    }

    /// Doubles capacity, unrolling the items so the oldest lands at index 0.
    fn grow(&mut self) {
        let cap = (self.buf.len() * 2).max(4);
        let mut buf: Vec<Option<T>> = (0..cap).map(|_| None).collect();
        for (i, slot) in buf.iter_mut().take(self.len).enumerate() {
            let src = (self.head + i) % self.buf.len();
            *slot = self.buf[src].take();
        }
        self.buf = buf;
        self.head = 0;
    }
}
