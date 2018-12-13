@extends('layouts.app')

@section('content')

<div class="list-group container exercises-listing">

    @if (count($exercises) === 0)
        <a href="{{ route('/exercise/create') }}" class="list-group-item list-group-item-action flex-column align-items-start rounded mb-2 pt-3 pl-4">
            <div class="d-flex w-80 justify-content-between">
                <h3 class="mb-1">You don't seem to have any exercises</h3>
                <h3 class="mb-2">+</h3>
            </div>
            <h5>Click on me to add an exercise!</h5>
        </a>
    @else
        @foreach ($exercises as $exercise)

        <a href="{{ url('/exercise/' . $exercise->id) }}" class="list-group-item list-group-item-action flex-column align-items-start rounded mb-2 pt-3 pl-4">
            <div class="d-flex w-100 justify-content-between">
                <h3 class="mb-1">{{str_limit($exercise->title, 50)}}</h3>
                <form method="POST" style="margin-top:2%;" action="{{ action('Web\ExerciseController@deleteExercise', ['id' => $exercise->id]) }}">
                {{ csrf_field() }}
                    <button type="submit" id="remove-button" class="btn btn-danger btn-xs rounded">
                        <i class="far fa-trash-alt"></i>
                    </button>
                </form>
            </div>
            <h5>{{ $exercise->description }}</h5>
        </a>

        @endforeach
    @endif

    <div class="rounded">
        {{ $exercises->links() }}
    </div>
</div>

@endsection
