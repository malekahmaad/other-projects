
public class SocialNetwork {
	private Graph<String> network;
	//constructor that starts network 
	public SocialNetwork() {
		network=new Graph<String>();
	}
	//function that adds users to the network 
	//if it finds exception from the type VertexExistException it throws error
	//(UserExistException)
	public void addUser(String user) throws UserExistException{
		try {
			network.addVertex(user);
		} catch (VertexExistException e) {
			throw new UserExistException();
		}
	}
	//function that adds relationship between two users in the network
	//if it finds exception from the type VertexNotFoundException
	//it throws error  (VertexNotExistException)
	public void addFriends(String user1, String user2) 
			throws UserNotFoundException{
		try {
			network.addEdge(user1, user2);
		} catch (VertexNotExistException e) {
			throw new UserNotFoundException();
		}
	}
	//function that checks if the users know each other from the bfs function
	//if one of the users is not existed it throws error from the type 
	//UserNotFoundException
	public boolean knows(String user1, String user2) 
			throws UserNotFoundException {
		try {
			network.getEdges(user1);
			network.getEdges(user2);
			if(network.bfs(user1, user2).size()!=0) {
				return true;
			}
			return false;
		} catch(VertexNotExistException e) {
			throw new UserNotFoundException();
		}

	}

}
