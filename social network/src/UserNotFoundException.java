
public class UserNotFoundException extends Exception{
	public UserNotFoundException() {
		super("this users dont exist in the graph");
	}

}
