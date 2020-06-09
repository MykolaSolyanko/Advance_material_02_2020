1. std::shared_ptr
2. std::unique_ptr vs std::shared_ptr. Move vs Copy
3. make_* как способ избежать утечки ресурсов при передачи умных указателей как аргументы функции. Возможен разный порядок вычисления аргументов.
4. Control block в std::shared_ptr. Зачем он нужен, какие он решает задачи, и возможные подводные камни при выделении ресурса при помощи std::make_shared.
5. Производительность std::unique_ptr и std::shared_ptr.
6. std::weak_ptr. Его применение, его влияние на блок управление в std::shared_ptr
7. Выделение динамического массива с помощью std::unique_ptr и std::shared_ptr. Специализация.
8. Зачем пользовательские deleter объекты как аргументы std::unique_ptr и std::shared_ptr. decltype как вывод сигнатуры функции.