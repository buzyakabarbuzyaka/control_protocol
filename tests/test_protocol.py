from app.writer import SerialController


# TODO: БАГ разобраться почему после релоада платы первый запрос без ответа
def test_create():
    sc = SerialController()


def test_connection():
    sc = SerialController()
    assert sc.request_position() == (0, 0)


def test_move():
    sc = SerialController()

    assert sc.move_motor(motor="A", direction="F", steps=100) == "0"
    assert sc.request_position() == (100, 0)

    assert sc.move_motor(motor="A", direction="R", steps=50) == "0"
    assert sc.request_position() == (50, 0)

    assert sc.move_motor(motor="B", direction="F", steps=100) == "0"
    assert sc.request_position() == (50, 100)

    assert sc.move_motor(motor="B", direction="R", steps=50) == "0"
    assert sc.request_position() == (50, 50)


def test_return_to_origin():
    sc = SerialController()

    assert sc.return_to_origin(motor="A", position="A") == "E"
    assert sc.request_position()[0] == 0

    assert sc.return_to_origin(motor="B", position="B") == "E"
    assert sc.request_position()[1] == 0

    assert sc.request_position() == (0, 0)
