void device1(AtomicQueue<Request> &from, AtomicQueue<Request> &to) {
    while (true) {
        Request req = from.pop();
        if (req.is_last) {
            to.push(req);
            break;
        }

        req.time_start_1 = get_time();
        req.documents = readDocumentsFromCSV(req.filename_in);
        standardizeDocumentLengths(req.documents);
        req.time_end_1 = get_time();

        to.push(req);
    }
}