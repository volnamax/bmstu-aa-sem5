void generator(AtomicQueue<Request> &q, const std::vector<std::string> &filenames,
               const std::vector<std::string> &filenames_out, int count_f) {
    for (size_t i = 0; i < count_f; ++i) {
        q.push({{}, {}, filenames[i], filenames_out[i]});
    }
    q.push({{}, {}, "", "", true}); 
}