
public class tester {

	public static void main(String[] args) throws VertexExistException, VertexNotExistException, UserExistException, UserNotFoundException {
		SocialNetwork data=new SocialNetwork();
		data.addUser("a");
		data.addUser("b");
		data.addUser("c");
		data.addUser("d");
		data.addUser("n");
		data.addFriends("a", "c");
		data.addFriends("b", "c");
		data.addFriends("b", "n");
		System.out.println(data.knows("a","a"));

	}

}
