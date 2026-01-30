class Person:
	def __init__(self, name, age):
		self.name = name
		self.age = age

	def sayHi(self):
		print(f"{self.name} На месте")

	def sayAge(self):
		print(f"{self.name, self.age}")


class Employee(Person):
		def __init__(self, name, age, role):
			super().__init__(name,age)
			self.role = role

		def sayGroup(self):
			print(f"Имя: {self.name} | Возраст: {self.age} | Должность : {self.role}")


person1 = Employee('Сергей', 18, "Программист")

person1.sayHi()
person1.sayAge()
person1.sayGroup()
