void device2(AtomicQueue<Request> &from, AtomicQueue<Request> &to) {
    while (true) {
        Request req = from.pop();
        if (req.is_last) {
            to.push(req);
            break;
        }

        req.time_start_2 = get_time();
        req.clusters = hierarchicalClustering(req.documents, MAX_DEPTH);
        req.time_end_2 = get_time();

        to.push(req);
    }
}