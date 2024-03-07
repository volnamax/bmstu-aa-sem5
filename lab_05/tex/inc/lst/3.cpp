void device3(AtomicQueue<Request> &from, AtomicQueue<Request> &completedRequests) {
    while (true) {
        Request req = from.pop();
        if (req.is_last) {
            break;
        }

        req.time_start_3 = get_time();
        saveClustersToJson(req.clusters, req.documents, req.filename_out);
        req.time_end_3 = get_time();
        completedRequests.push(req);
    }
}