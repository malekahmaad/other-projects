import java.util.ArrayList;

public class Graph <E>{
	private ArrayList<ArrayList<E>> data;
	//constructor that starts the data with size 0
	public Graph() {
		data=new ArrayList<ArrayList<E>>();
	}
	//function that adds the elements 
	//if the element is existed the function throws error 
	public void addVertex(E ver) throws VertexExistException {
		for(int i=0;i<data.size();i++) {
			if(data.get(i).get(0)==ver)
				throw new VertexExistException();
		}
		ArrayList<E> node=new ArrayList<E>();
		node.add(ver);
		data.add(node);
	}
	//function that makes a relationship between two elements 
	//if one of them at least is not existed the function throws error 
	public void addEdge(E ver1, E ver2) throws VertexNotExistException{
		boolean excisted=false;
		boolean excisted2=false;
		for(int i=0;i<data.size();i++) {
			if(data.get(i).get(0)==ver1)
				excisted=true;
			if(data.get(i).get(0)==ver2)
				excisted2=true;
		}
		if(excisted==false || excisted2==false)
			throw new VertexNotExistException();
		for(int j=0;j<data.size();j++) {
			if(data.get(j).get(0)==ver1)
				data.get(j).add(ver2);
			if(data.get(j).get(0)==ver2)
				data.get(j).add(ver1);
		}
	}
	//function that returns the elements that have relationship with thee 
	//ver and put them in arrayList
	//if ver doesnt exist it throws error
	public ArrayList<E> getEdges(E ver) throws VertexNotExistException {
		boolean excisted=false;
		int place=0;
		ArrayList<E> Edges=new ArrayList<E>();
		for(int i=0;i<data.size();i++) {
			if(data.get(i).get(0)==ver) {
				excisted=true;
				place=i;
				break;
			}
		}
		if(excisted==false)
			throw new VertexNotExistException();
		for(int j=1;j<data.get(place).size();j++) {
			Edges.add(data.get(place).get(j));
		}
		return Edges;
	}
	//function that returns all the elements in arrayList
	public ArrayList<E> getVertices() {
		ArrayList<E> Vertices=new ArrayList<E>();
		for(int i=0;i<data.size();i++) {
			Vertices.add(data.get(i).get(0));
		}
		return Vertices;
	}
	//function that finds the first way from the element (from) to the element
	//(to) and it returns it if the arrayList (ways) size is zero that means
	//there is no way to the element (to) because it checked all the elements 
	//by checking the first element in the arrayList then checking the 
	//relationships for the last element in the first element in the array
	//ways if it finds the two elements in the arrays into the array ways
	//it returns the array that contains them  
	//if one of the elements at least is not existed it goes to the catch 
	//and do nothing
	public ArrayList<E> bfs(E from, E to) {
		ArrayList<ArrayList<E>> ways=new ArrayList<ArrayList<E>>();
		ArrayList<E> way1=new ArrayList<E>();
		way1.add(from);
		ways.add(way1);
		for(;;) {
			if(ways.size()==0)
				return new ArrayList<E>();
			for(int i=0;i<ways.size();i++) {
				if(ways.get(i).contains(from)==true && 
						ways.get(i).contains(to)==true)
					return ways.get(i); 
			}
			try {
				ArrayList<E> saved2=this.getEdges(to);
				ArrayList<E> saved=ways.get(0);
				ArrayList<E> edges=this.getEdges(saved.get(saved.size()-1));
				for(int j=0;j<edges.size();j++) {
					if(saved.contains(edges.get(j))==false) {
						ArrayList<E> putting=new ArrayList<E>(saved);
						putting.add(edges.get(j));
						ways.add(putting);
					}
				}
				ways.remove(0);
			} catch(VertexNotExistException e) {

			}

		}

	}


}
